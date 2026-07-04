#encoding=utf8
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.preprocessing import StandardScaler

def ada_classifier(train_data,train_label,test_data):
    '''
    input:train_data(ndarray):训练数据
          train_label(ndarray):训练标签
          test_data(ndarray):测试标签
    output:predict(ndarray):预测结果
    '''
    #********* Begin *********#
    scaler = StandardScaler()
    train_data_scaled = scaler.fit_transform(train_data)
    test_data_scaled = scaler.transform(test_data)

    # 修改基分类器参数：增加决策树的最大深度，以捕获更复杂的特征关系
    # 同时增加迭代轮数，配合稍小的学习率以增强泛化和拟合能力
    base_clf = DecisionTreeClassifier(max_depth=3)
    clf = AdaBoostClassifier(base_clf, n_estimators=100, learning_rate=0.8)
    
    clf.fit(train_data_scaled, train_label)
    predict = clf.predict(test_data_scaled)
    #********* End *********# 
    return predict