import numpy as np
import math


# GM是 MxK的存储格式
# 软件实现上可以直接mk2k1mk0，硬件上不行
class GM:
    def __init__(self, M, K):
        self.M = M
        self.K = K
        self.gm = np.zeros((M, K), dtype=int)

    #print (m, k) @ gm
    def __str__(self):
        res = ""
        # 找出最大值的位数，用于动态调整宽度
        max_value = np.max(self.gm)
        value_width = max(len(str(max_value)), 1)
        for m in range(self.M):
            for k in range(self.K):
                #对齐打印
                res += f"({m},{k})@{self.gm[m][k]:{value_width}} |"
            res += "\n"
        return res
    
    
    
if __name__ == "__main__":
    gm = GM(7, 7)
    print(gm)
    print(gm.mk2k1mk0(4))
