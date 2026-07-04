#encoding=utf8

import numpy as np

#adaboost算法
class AdaBoost:
    '''
    input:n_estimators(int):迭代轮数
          learning_rate(float):弱分类器权重缩减系数
    '''
    def __init__(self, n_estimators=50, learning_rate=1.0):
        self.clf_num = n_estimators
        self.learning_rate = learning_rate
    
    def init_args(self, datasets, labels):
        
        self.X = datasets
        self.Y = labels
        self.M, self.N = datasets.shape
        
        # 弱分类器数目和集合
        self.clf_sets = []
        
        # 初始化weights
        self.weights = [1.0/self.M]*self.M
        
        # G(x)系数 alpha
        self.alpha = []    
    def _G(self, features, labels, weights):
        '''
        input:features(ndarray):数据特征
              labels(ndarray):数据标签
              weights(ndarray):样本权重系数
        '''
        #********* Begin *********#
        m = len(features)
        error = 100000.0 # 无穷大
        best_v = 0.0
        # 单维特征
        features_1d = []
        if len(features.shape) == 1:
            features_1d = features
            features = np.zeros((m, 1))
            features[:, 0] = features_1d
            
        n = features.shape[1]
        
        best_d = 'positive'
        best_features = []
        best_axis = 0
        
        for j in range(n):
            features_1d = features[:, j]
            # 特征的最大值和最小值，步长
            min_f, max_f = features_1d.min(), features_1d.max()
            step_size = (max_f - min_f) / 10.0
            
            for i in range(1, 11):
                v = min_f + i * step_size
                for direct in ['positive', 'negative']:
                    compare_array = np.ones(m)
                    if direct == 'positive':
                        compare_array[features_1d < v] = -1
                    else:
                        compare_array[features_1d > v] = -1
                    
                    weights_np = np.array(weights)
                    labels_np = np.array(labels)
                    e = sum(weights_np[compare_array != labels_np])
                    if e < error:
                        error = e
                        best_v = v
                        best_d = direct
                        best_features = compare_array.copy()
                        best_axis = j
                        
        return best_v, best_d, error, best_features, best_axis

    def G(self, feature, clf_v, direct):
        if direct == 'positive':
            return 1 if feature >= clf_v else -1
        else:
            return 1 if feature <= clf_v else -1

    def fit(self, X, y):
        self.init_args(X, y)
        for epoch in range(self.clf_num):
            best_v, best_d, error, best_features, best_axis = self._G(self.X, self.Y, self.weights)
            
            if error > 0.5:
                break
                
            # 计算alpha
            alpha = 0.5 * np.log((1 - error) / max(error, 1e-16))
            
            # 记录此时的弱分类器
            self.clf_sets.append((best_axis, best_v, best_d))
            self.alpha.append(alpha)
            
            # 更新权重
            Z = sum([self.weights[i] * np.exp(-alpha * self.Y[i] * best_features[i]) for i in range(self.M)])
            for i in range(self.M):
                self.weights[i] = self.weights[i] * np.exp(-alpha * self.Y[i] * best_features[i]) / Z
        #********* End *********#            
    def predict(self, feature):
        result = 0.0
        for i in range(len(self.clf_sets)):
            axis, clf_v, direct = self.clf_sets[i]
            f_input = feature[axis]
            result += self.alpha[i] * self.G(f_input, clf_v, direct)
        # sign
        return 1 if result > 0 else -1
    
    def score(self, X_test, y_test):
        right_count = 0
        for i in range(len(X_test)):
            feature = X_test[i]
            if self.predict(feature) == y_test[i]:
                right_count += 1
        
        return right_count / len(X_test)