import numpy as np


# v1 basic matrix multiplication

M = 16
K = 32
N = 8
IA = np.zeros((M, K))
weight = np.zeros((K, N))
OA = np.zeros((N, M))
weight_buffer_width = 4
ia_buffer_height = 4

# move from dram to buffer
def mvin(W):
    pass

# move from buffer to dram
def mvout(OA):
    pass

def matmul_v1():
    for m in range(M):
        for n in range(N):
            OA[n, m] = 0
            for k in range(K):
                OA[n, m] += IA[m, k] * weight[k, n]

    
# v2 if systolic array = 2x2 , basic compute unit = 2x2
def matmul_v2():
    for m in range(M):
        for n in range(2):
            OA[n, m] = 0
            for k in range(2):
                OA[n, m] += IA[m, k] * weight[k, n]

# v3 if M=1, N > 2, K > 2 , basic compute unit cannot hold all the data
def matmul_v3():
    # 这里不考虑补全
    N0 = 2
    N1 = N // N0
    K0 = 2
    K1 = K // K0
    for m in range(M):
        for n1 in range(N1):
            # OA每次计算的是一个块，块大小为N0*1
            OA[n1*N0 : (n1+1)*N0, m] = 0
            for k in range(K1):
                # 最小计算单元 N0 X K0
                for n0 in range(N0):
                    for k0 in range(K0):
                        # 外层循环是N1 K1 , 内循环是 N0 K0，一次算一个点，下面是每个具体的点的坐标
                        n_idx = n1*N0 + n0
                        k_idx = k*K0 + k0
                        OA[n_idx, m] += IA[m, k_idx] * weight[k_idx, n_idx]


# v4 add mvin and mvout
def matmul_v4():
    # 这里不考虑补全
    N0 = 2
    N1 = N // N0
    K0 = 2
    K1 = K // K0
    for m in range(M):
        # 一次load所有weight data
        mvin(weight[0:K, 0:N])
        # 一次load 1*K的data
        mvin(IA[m:m+1, 0:K])
        for n1 in range(N1):
            # OA每次计算的是一个块，块大小为N0*1
            OA[n1*N0 : (n1+1)*N0, m] = 0
            for k in range(K1):
                # 最小计算单元 N0 X K0
                for n0 in range(N0):
                    for k0 in range(K0):
                        # 外层循环是N1 K1 , 内循环是 N0 K0，一次算一个点，下面是每个具体的点的坐标
                        n_idx = n1*N0 + n0
                        k_idx = k*K0 + k0
                        OA[n_idx, m] += IA[m, k_idx] * weight[k_idx, n_idx]
        # input 每次load一行，对应于mvout输出一行
        mvout(OA[0:N, m:m+1])

# v5 if weight buffer size < N * K
def matmul_v5():
    # 这里不考虑补全
    N0 = 2
    N1 = weight_buffer_width
    N2 = N // (N1 * N0)
    K0 = 2
    K1 = K // K0
    for m in range(M):
        # 一次load 1*K的input data
        mvin(IA[m:m+1, 0:K])
        for n2 in range(N2):
            # 每次load K * N1 * N0的数据, K*N1*N0 < N*K
            mvin(weight[0:K, n2*N1*N0:(n2+1)*N1*N0])
            # OA每次计算的是一个块，块大小为N0*N1 * 1 , N方向的维度要随着切片大小变化
            OA[n2*N1*N0 : (n2+1)*N1*N0, m:m+1] = 0
            for n1 in range(N1):
                for k in range(K1):
                # 最小计算单元 N0 X K0
                    for n0 in range(N0):
                        for k0 in range(K0):
                            # n方向有3个维度，都要考虑
                            n_idx = n2*N1*N0 + n1*N0 + n0
                            k_idx = k*K0 + k0
                            OA[n_idx, m] += IA[m, k_idx] * weight[k_idx, n_idx]
            # 输出不仅考虑input mvin, 还需要考虑weight mvin，mvout跟两个mvin强绑定
            mvout(OA[n2*N1*N0:(n2+1)*N1*N0, m:m+1])


# v6 if input activation buffer size > 1*K
def matmul_v6():
        # 这里不考虑补全
    N0 = 2
    N1 = weight_buffer_width
    N2 = N // (N1 * N0)
    K0 = 2
    K1 = K // K0
    M1 = ia_buffer_height
    M2 = 16 # all_data / K 

    for m2 in range(M2):
        # IA buffer store M1*K , 先整个取进来，后面再挨个读取
        mvin(IA[m2*M1:(m2+1)*M1, 0:K])
        for n2 in range(N2):
            # 每次load K * N1 * N0的数据, K*N1*N0 < N*K
            mvin(weight[0:K, n2*N1*N0:(n2+1)*N1*N0])
            # OA大小为N1*N0 x M1
            OA[n2*N1*N0:(n2+1)*N1*N0, m2*M1:(m2+1)*M1] = 0
            for m1 in range(M1):
                for n1 in range(N1):
                    for k1 in range(K1):
                        m_idx = m2*M1 + m1
                        for n0 in range(N0):
                            for k0 in range(K0):
                                k_idx = k1*K0 + k0
                                n_idx = n2*N1*N0 + n1*N0 + n0
                                OA[n_idx, m_idx] += IA[m_idx, k_idx] * weight[k_idx, n_idx]
            # 一次mov out N1*N0 x M1
            mvout(OA[n2*N1*N0:(n2+1)*N1*N0, m2*M1:(m2+1)*M1])


# v7 