from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt

def digit_predict(train_image, train_label, test_image):
    '''
    实现功能：训练模型并输出预测结果
    :param train_sample: 包含多条训练样本的样本集，类型为ndarray,shape为[-1, 8, 8]
    :param train_label: 包含多条训练样本标签的标签集，类型为ndarray
    :param test_sample: 包含多条测试样本的测试集，类型为ndarry
    :return: test_sample对应的预测标签
    '''

    #************* Begin ************#
    # 将图像数据拉平为二维数组 (n_samples, n_features)
    train_features = train_image.reshape(train_image.shape[0], -1)
    test_features = test_image.reshape(test_image.shape[0], -1)
    
    # 对数据进行标准化处理
    scaler = StandardScaler()
    train_features = scaler.fit_transform(train_features)
    test_features = scaler.transform(test_features)
    
    # 初始化逻辑回归分类器并训练
    classifier = LogisticRegression(max_iter=2000, solver='sag', C=1.0)
    classifier.fit(train_features, train_label)
    
    # 对测试集进行预测并返回结果
    predict_labels = classifier.predict(test_features)
    return predict_labels
    #************* End **************#