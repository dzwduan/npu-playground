import numpy as np
from reqAlign import RdGmReq, AlignedRdGmReq



# 记录RdGmReq中的startOffest + endOffset
class ReqTable:
    def __init__(self, num):
        # self.align_len = align_len
        # self.startOffset = startOffset
        # self.endOffset = endOffset
        # self.reqId = reqId
        self.table = np.zeros((num, 3), dtype=int)

    def generate(self, startAddr : list[int], startOffset : list[int], endOffset : list[int], reqId : list[int]):
        for i in range(len(reqId)):
            self.table[i][0] = startAddr[i]
            self.table[i][1] = startOffset[i]
            self.table[i][2] = endOffset[i]
        return self.table

