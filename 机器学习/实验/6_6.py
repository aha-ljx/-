#encoding=utf8
from sklearn.svm import SVC

def svm_classifier(train_data,train_label,test_data):
    '''
    input:train_data(ndarray):训练样本
          train_label(ndarray):训练标签
          test_data(ndarray):测试样本
    output:predict(ndarray):预测结果      
    '''
    #********* Begin *********#
    # 实例化SVC分类器，默认使用RBF高斯核函数
    classifier = SVC()
    # 使用训练集进行训练拟合
    classifier.fit(train_data, train_label)
    # 使用训练好的模型对测试集进行预测
    predict = classifier.predict(test_data)
    #********* End *********#
    return predict