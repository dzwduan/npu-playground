import numpy as np
import math


# GM是 MxK的存储格式
# 软件实现上可以直接mk2k1mk0，硬件上不行
class GM:
    def __init__(self, M, K):
        self.M = M
        self.K = K
        self.gm = np.arange(1, M*K + 1, dtype=int).reshape(M, K)
        self.k1mk0 = None

    #print (m, k) @ gm
    def __str__(self):
        res = ""
        # for mk , 找出最大值的位数，用于动态调整宽度
        if(self.k1mk0 is None):
            max_value = np.max(self.gm)
            value_width = max(len(str(max_value)), 1)
            for m in range(self.M):
                for k in range(self.K):
                    #对齐打印
                    res += f"({m},{k})@{self.gm[m][k]:{value_width}} |"
                res += "\n"
        else:
            K1, M, K0 = self.k1mk0.shape
            res = ""
            for k1 in range(K1):
                for m in range(M):
                    for k0 in range(K0):
                        res += f"({m},{k1*K0+k0})@{self.k1mk0[k1][m][k0]} |"
                    res += "\n"
                res += "\n"
        return res

    # 实现GM根据维度变化补零的效果, 假设是MK -> K1MK0
    def mk2k1mk0(self, K0):
        M, K = self.gm.shape
        K1 = (K+K0-1) // K0

        MK1K0 = np.zeros((M, K1, K0), dtype=int)
        for m in range(M):
            for k in range(K):
                MK1K0[m][k // K0][k % K0] = self.gm[m][k]

        self.k1mk0 = MK1K0.transpose(1, 0, 2)
        return self.k1mk0

if __name__ == "__main__":
    gm = GM(7, 7)
    print(gm)
    gm.mk2k1mk0(4)
    print(gm)