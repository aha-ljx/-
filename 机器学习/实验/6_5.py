#encoding=utf8
import numpy as np

class SVM:
    def __init__(self, max_iter=100, kernel='linear'):
        '''
        input:max_iter(int):最大训练轮数
              kernel(str):核函数，等于'linear'表示线性，等于'poly'表示多项式
        '''
        self.max_iter = max_iter
        self._kernel = kernel
    #初始化模型
    def init_args(self, features, labels):
        self.m, self.n = features.shape
        self.X = features
        self.Y = labels
        self.b = 0.0
        # 将Ei保存在一个列表里
        self.alpha = np.ones(self.m)
        self.E = [self._E(i) for i in range(self.m)]
        # 松弛变量
        self.C = 1.0
    #********* Begin *********#    
    # g(x)预测值，输入xi（X[i]）
    def _g(self, i):
        r = self.b
        for j in range(self.m):
            if self.alpha[j] > 0:
                r += self.alpha[j] * self.Y[j] * self.kernel(self.X[i], self.X[j])
        return r

    # 核函数
    def kernel(self, x1, x2):
        if self._kernel == 'linear':
            return np.dot(x1, x2)
        elif self._kernel == 'poly':
            return (np.dot(x1, x2) + 1) ** 2
        return 0

    # 选择参数并进行训练
    def fit(self, features, labels):
        # 重新初始化参数，极其重要：alpha 必须初始化为 0，以满足 sum(alpha_i * y_i) = 0 的约束
        self.m, self.n = features.shape
        self.X = features
        self.Y = labels
        self.b = 0.0
        self.alpha = np.zeros(self.m)
        self.C = 1.0

        # Simplified SMO 算法
        for t in range(self.max_iter):
            alpha_pairs_changed = 0
            for i in range(self.m):
                Ei = self._g(i) - self.Y[i]
                
                # 检查 KKT 条件 (加入容差)
                tol = 1e-3
                if (self.Y[i] * Ei < -tol and self.alpha[i] < self.C) or (self.Y[i] * Ei > tol and self.alpha[i] > 0):
                    # 随机选择第二个参数 j
                    j = i
                    while j == i:
                        j = np.random.randint(0, self.m)
                        
                    Ej = self._g(j) - self.Y[j]
                    
                    alpha_i_old = self.alpha[i].copy()
                    alpha_j_old = self.alpha[j].copy()
                    
                    # 边界计算
                    if self.Y[i] != self.Y[j]:
                        L = max(0, self.alpha[j] - self.alpha[i])
                        H = min(self.C, self.C + self.alpha[j] - self.alpha[i])
                    else:
                        L = max(0, self.alpha[j] + self.alpha[i] - self.C)
                        H = min(self.C, self.alpha[j] + self.alpha[i])
                        
                    if L == H:
                        continue
                        
                    # 计算 eta
                    eta = self.kernel(self.X[i], self.X[i]) + self.kernel(self.X[j], self.X[j]) - 2 * self.kernel(self.X[i], self.X[j])
                    if eta <= 0:
                        continue
                        
                    # 更新 alpha_j
                    self.alpha[j] += self.Y[j] * (Ei - Ej) / eta
                    
                    # 裁剪 alpha_j
                    if self.alpha[j] > H:
                        self.alpha[j] = H
                    elif self.alpha[j] < L:
                        self.alpha[j] = L
                        
                    if abs(self.alpha[j] - alpha_j_old) < 1e-5:
                        continue
                        
                    # 更新 alpha_i
                    self.alpha[i] += self.Y[i] * self.Y[j] * (alpha_j_old - self.alpha[j])
                    
                    # 更新 b
                    b1 = self.b - Ei - self.Y[i] * (self.alpha[i] - alpha_i_old) * self.kernel(self.X[i], self.X[i]) - self.Y[j] * (self.alpha[j] - alpha_j_old) * self.kernel(self.X[i], self.X[j])
                    b2 = self.b - Ej - self.Y[i] * (self.alpha[i] - alpha_i_old) * self.kernel(self.X[i], self.X[j]) - self.Y[j] * (self.alpha[j] - alpha_j_old) * self.kernel(self.X[j], self.X[j])
                    
                    if 0 < self.alpha[i] < self.C:
                        self.b = b1
                    elif 0 < self.alpha[j] < self.C:
                        self.b = b2
                    else:
                        self.b = (b1 + b2) / 2
                        
                    alpha_pairs_changed += 1
                    
            if alpha_pairs_changed == 0:
                pass

    #********* End *********#      
    def predict(self, data):
        r = self.b
        for i in range(self.m):
            r += self.alpha[i] * self.Y[i] * self.kernel(data, self.X[i])
        return 1 if r > 0 else -1
    def score(self, X_test, y_test):
        right_count = 0
        for i in range(len(X_test)):
            result = self.predict(X_test[i])
            if result == y_test[i]:
                right_count += 1
        return right_count / len(X_test)
    def _weight(self):
        yx = self.Y.reshape(-1, 1)*self.X
        self.w = np.dot(yx.T, self.alpha)
        return self.w