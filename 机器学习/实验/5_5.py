from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.preprocessing import StandardScaler


def news_predict(train_sample, train_label, test_sample):
    '''
    训练模型并进行预测，返回预测结果
    :param train_sample:原始训练集中的新闻文本，类型为ndarray
    :param train_label:训练集中新闻文本对应的主题标签，类型为ndarray
    :param test_sample:原始测试集中的新闻文本，类型为ndarray
    :return 预测结果，类型为ndarray
    '''

    #********* Begin *********#
    # 1. 调整词袋模型参数：加入 stop_words='english' 去除英文停用词（若是中文任务请改用相应的中文停用词表），
    # 并使用 ngram_range=(1,2) 提取连续的词组特征，这对提升正确率非常显著。
    vec = CountVectorizer(stop_words='english', ngram_range=(1, 2), max_df=0.8)
    train_matrix = vec.fit_transform(train_sample)
    
    # 2. 提取 TF-IDF 特征：加入 sublinear_tf=True 减弱高频词带来的过度影响
    tfidf = TfidfTransformer(sublinear_tf=True)
    train_tfidf = tfidf.fit_transform(train_matrix)
    test_matrix = vec.transform(test_sample)
    test_tfidf = tfidf.transform(test_matrix)
    
    # 注意：移除 StandardScaler。在文本类任务中，TF-IDF 已经完成了行级归一化，
    # 额外进行列级标准化反而会破坏文档的稀疏性和统计分布规律，甚至降低朴素贝叶斯的准确率！
    
    # 3. 朴素贝叶斯：将 alpha 进一步调低到 0.01，减少对零频率特征的过度惩罚
    mnb = MultinomialNB(alpha=0.01)
    mnb.fit(train_tfidf, train_label)
    
    return mnb.predict(test_tfidf)
    #********* End *********#