import numpy as np

def calcInfoGain(feature, label, index):
    '''
    计算信息增益
    :param feature:测试用例中字典里的feature，类型为ndarray
    :param label:测试用例中字典里的label，类型为ndarray
    :param index:测试用例中字典里的index，即feature部分特征列的索引。该索引指的是feature中第几个特征，如index:0表示使用第一个特征来计算信息增益。
    :return:信息增益，类型float
    '''
    # 计算总熵
    def calcEntropy(label):
        count = np.bincount(label)
        prob = count / len(label)
        result = -np.sum(prob * np.log2(prob + 1e-10))
        return result
    totalEntropy = calcEntropy(label)
    # 计算条件熵
    def calcCondEntropy(feature, label, index):
        uniqueValues = np.unique(feature[:, index])
        condEntropy = 0.0
        for value in uniqueValues:
            sublabel = label[feature[:,index] == value]
            prob = len(sublabel) / len(label)
            condEntropy += prob * calcEntropy(sublabel)
        return condEntropy
    condEntropy = calcCondEntropy(feature, label, index)
    # 计算信息增益
    infoGain = totalEntropy - condEntropy
    return infoGain