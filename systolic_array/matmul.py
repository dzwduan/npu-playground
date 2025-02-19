import numpy as np 
import math

# matmul with three loop
def matmulWithThreeLoop(A, B):
    """
    This function is used to calculate the matrix multiplication of A and B
    using three loops.
    改变循环顺序, 不影响正确性
    """
    assert len(A.shape) == 2, "A should be a 2D matrix"
    assert len(B.shape) == 2, "B should be a 2D matrix"
    assert A.shape[1] == B.shape[0], "The column number of A should be equal to the row number of B"

    m, n = A.shape
    n, p = B.shape
    C = np.zeros((m, p))
    for i in range(m):
        for j in range(p):
            for k in range(n):
                C[i, j] += A[i, k] * B[k, j]
    return C


def innerProduct(X, Y):
    """
    This function is used to calculate the inner product of X and Y.
    X : n x 1 array
    Y : n x 1 array
    内积的结果是一个数
    """
    assert len(X) == len(Y), "The length of X should be equal to the length of Y"
    assert len(X.shape) == 1, "X should be a 1D array"
    assert len(Y.shape) == 1, "Y should be a 1D array"
    Z = 0
    for i in range(X.shape[0]):
        Z += X[i] * Y[i]
    return Z


def outerProduct(X, Y):
    """
    This function is used to calculate the outer product of X and Y.
    X : n x 1 array
    Y : m x 1 array
    外积的结果是一个n x m的矩阵
    """
    assert len(X) == len(Y), "The length of X should be equal to the length of Y"
    assert len(X.shape) == 1, "X should be a 1D array"
    assert len(Y.shape) == 1, "Y should be a 1D array"
    z = np.zeros((X.shape[0], Y.shape[0]))
    for i in range(X.shape[0]):
        for j in range(Y.shape[0]):
            z[i, j] += X[i] * Y[j]
    return z


# matmul with inner product
def matmulWithInnerProduct(A, B):
    """
    This function is used to calculate the matrix multiplication of A and B
    using inner product.
    A的行向量和B的列向量做内积
    """
    assert len(A.shape) == 2, "A should be a 2D matrix"
    assert len(B.shape) == 2, "B should be a 2D matrix"
    assert A.shape[1] == B.shape[0], "The column number of A should be equal to the row number of B"

    m, n = A.shape
    n, p = B.shape
    C = np.zeros((m, p))
    for i in range(m):
        for j in range(p):
            C[i, j] = innerProduct(A[i, :], B[:, j])
    return C

def matmulWithOuterProduct(A, B):
    """
    This function is used to calculate the matrix multiplication of A and B
    using outer product.
    X的列向量和Y的行向量做外积, 外积的结果element-wise相加, 得到最终结果
    """
    assert len(A.shape) == 2, "A should be a 2D matrix"
    assert len(B.shape) == 2, "B should be a 2D matrix"
    assert A.shape[1] == B.shape[0], "The column number of A should be equal to the row number of B"

    m, n = A.shape
    n, p = B.shape
    C = np.zeros((m, p))
    for i in range(n):
        print("A.shape", A[:, i].shape)
        print("B.shape", B[i, :].shape)
        C += outerProduct(A[:, i], B[i, :])
    return C


def matmulTilingWithThreeLoop(X, Y, QU, KU, CU):
    """
    This function is used to calculate the matrix multiplication of X and Y
    using tiling.
    QU KU CU : 分别表示tile的3个维度
    """
    assert len(X.shape) == 2, "X should be a 2D matrix"
    assert len(Y.shape) == 2, "Y should be a 2D matrix"
    assert X.shape[1] == Y.shape[0], "The column number of X should be equal to the row number of Y"

    Q, C = X.shape
    C, K = Y.shape
    Z = np.zeros((Q, K))

    Q1 = (Q + QU - 1) // QU
    C1 = (C + CU - 1) // CU 
    K1 = (K + KU - 1) // KU

    # 这里的维度顺序改变不影响正确性
    # for q1 in range(Q1):
    #     for c1 in range(C1):
    #         for k1 in range(K1):
    #             q = q1 * QU
    #             c = c1 * CU
    #             k = k1 * KU
    #             for i in range(QU):
    #                 for j in range(CU):
    #                     for k in range(KU):
    #                         if q + i < Q and c + j < C and k + k < K:
    #                             Z[q + i, k + k] += X[q + i, c + j] * Y[c + j, k + k]

    for q1 in range(Q1):
        for c1 in range(C1):
            for k1 in range(K1):
                q_start = q1 * QU
                c_start = c1 * CU
                k_start = k1 * KU
                #注意边界条件
                q_end = min(q_start + QU, Q)
                c_end = min(c_start + CU, C)
                k_end = min(k_start + KU, K)
                Z[q_start:q_end, k_start:k_end] += matmulWithThreeLoop(X[q_start:q_end, c_start:c_end], Y[c_start:c_end, k_start:k_end])
    return Z

def matmulTilingWithThreeLoop2(X, Y, QU, KU, CU, QTS, KTS, CTS):
    """"
    X, Y 是输入矩阵
    QU, KU, CU 是基本块大小
    QTS : 并行计算QT循环的PE数量
    QTT : 计算QTT次才能覆盖完整的Q
    """

    assert len(X.shape) == len(Y.shape) and len(X.shape) == 2
    assert X.shape[1] == Y.shape[0]
    Q, C = X.shape
    _, K = Y.shape
    Z = np.zeros((Q, K))

    # 计算tile的数量, tile大小对应到一个PE的大小
    QT = (Q + QU - 1) // QU
    CT = (C + CU - 1) // CU
    KT = (K + KU - 1) // KU

    # 计算完成所需要的次数
    QTT = (QT + QTS - 1) // QTS
    CTT = (CT + CTS - 1) // CTS
    KTT = (KT + KTS - 1) // KTS

    for qtt in range(QTT):
        for ctt in range(CTT):
            for ktt in range(KTT):
                for qts in range(QTS):
                    for cts in range(CTS):
                        for kts in range(KTS):
                            # 计算当时是第几个tile
                            qt = qtt * QTS + qts
                            ct = ctt * CTS + cts
                            kt = ktt * KTS + kts
                            if qt < QT and ct < CT and kt < KT:
                                q_start = qt * QU
                                c_start = ct * CU
                                k_start = kt * KU
                                q_end = min(q_start + QU, Q)
                                c_end = min(c_start + CU, C)
                                k_end = min(k_start + KU, K)
                                Z[q_start:q_end, k_start:k_end] += matmulWithThreeLoop(X[q_start:q_end, c_start:c_end], Y[c_start:c_end, k_start:k_end])

    return Z

def matmulTilingWithThreeLoop3(X, Y, QU, KU, CU, QTS, KTS, CTS):
    """"
    X, Y 是输入矩阵
    QU, KU, CU 是基本块大小
    QTS : 并行计算QT循环的PE数量
    QTT : 计算QTT次才能覆盖完整的Q
    """

    assert len(X.shape) == len(Y.shape) and len(X.shape) == 2
    assert X.shape[1] == Y.shape[0]
    Q, C = X.shape
    _, K = Y.shape
    Z = np.zeros((Q, K))

    # 计算tile的数量, tile大小对应到一个PE的大小
    QT = (Q + QU - 1) // QU
    CT = (C + CU - 1) // CU
    KT = (K + KU - 1) // KU

    # 计算完成所需要的次数
    QTT = (QT + QTS - 1) // QTS
    CTT = (CT + CTS - 1) // CTS
    KTT = (KT + KTS - 1) // KTS

    for qtt in range(QTT):
        for ktt in range(KTT):
            for qts in range(QTS):
                for kts in range(KTS):
                    # 计算当时是第几个tile
                    qt = qtt * QTS + qts
                    kt = ktt * KTS + kts
                    q_start = qt * QU
                    k_start = kt * KU
                    q_end = min(q_start + QU, Q)
                    k_end = min(k_start + KU, K)
                    for cts in range(CTS):
                        for ctt in range(CTT):
                            ct = ctt * CTS + cts
                            if qt < QT and ct < CT and kt < KT:
                                c_start = ct * CU
                                c_end = min(c_start + CU, C)
                                Z[q_start:q_end, k_start:k_end] += matmulWithThreeLoop(X[q_start:q_end, c_start:c_end], Y[c_start:c_end, k_start:k_end])
    return Z


# 主要参考 https://zhuanlan.zhihu.com/p/6965244634 , 最后的算法比较晦涩, 暂时不想看
def matmulWithPE(X, Y, QU, KU, CU, QTS, KTS, CTS):
    """"
    X, Y 是输入矩阵
    QU, KU, CU 是基本块大小
    QTS : 有多少组PE
    KTS : 有多少组PE
    CTS : 每几个PE通过Router进行reduce
    QTT : 计算QTT次才能覆盖完整的Q

    On-chip Buffer: 指代两个input tensor 和一个output tensor
    PE Buffer : 每个PE保护input buffer + weight buffer + output buffer , 使用X_pe, Y_pe, Z_pe表示

    """

    assert len(X.shape) == len(Y.shape) and len(X.shape) == 2
    assert X.shape[1] == Y.shape[0]
    Q, C = X.shape
    _, K = Y.shape
    Z = np.zeros((Q, K))

    # 计算tile的数量, tile大小对应到一个PE的大小
    QT = (Q + QU - 1) // QU
    CT = (C + CU - 1) // CU
    KT = (K + KU - 1) // KU

    # 计算完成所需要的次数
    QTT = (QT + QTS - 1) // QTS
    CTT = (CT + CTS - 1) // CTS
    KTT = (KT + KTS - 1) // KTS

    # 新增PE！
    PE_NUM = 16
    X_pe = np.zeros((PE_NUM, Q, C))
    Y_pe = np.zeros((PE_NUM, C, K))
    Z_pe = np.zeros((PE_NUM, Q, K))



    for qtt in range(QTT):
        for ktt in range(KTT):
            for qts in range(QTS):
                for kts in range(KTS):
                    # 计算当时是第几个tile
                    qt = qtt * QTS + qts
                    kt = ktt * KTS + kts
                    q_start = qt * QU
                    k_start = kt * KU
                    q_end = min(q_start + QU, Q)
                    k_end = min(k_start + KU, K)
                    # 参考Q X K的切面图
                    reduce_group_id = qts * KTS + kts
                    # 遍历reduce的每一组
                    for cts in range(CTS):
                        pe_id = reduce_group_id * CTS + cts
                        # 每个PE完成CTT次matmul
                        for ctt in range(CTT):
                            if qt < QT and kt < KT and ct < CT:
                                # 
                                ct = ctt * CTS + cts
    return Z

