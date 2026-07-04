import numpy as np

#实现核函数
def kernel(x,sigma=1.0):
    '''
    input:x(ndarray):样本
    output:x(ndarray):转化后的值
    '''    
    #********* Begin *********#
    # 针对异或问题，新增交互维度 z = (x1 - x2)^2
    z = (x[:, 0] - x[:, 1]) ** 2
    
    # 因为 z 是一维的，我们需要将它转为列向量才能拼接到 x 后面
    z = z.reshape(-1, 1)
    
    # 将新维度 z 拼接到原始数据 x 后面，构造成三维坐标
    x = np.concatenate((x, z), axis=1)
    #********* End *********#
    return x