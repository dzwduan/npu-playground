import numpy as np
from reqAlign import RdGmReq, AlignedRdGmReq



# 记录RdGmReq中的startOffest + endOffset
class reqTable:
    def __init__(self, startOffset : list[int], endOffset : list[int], reqId : list[int], align_len: int):
        self.align_len = align_len
        self.startOffset = startOffset
        self.endOffset = endOffset
        self.reqId = reqId
        self.table = np.zeros((len(reqId), 2), dtype=int)
        
    def generate_table(self):
        for i in range(len(self.reqId)):
            self.table[i][0] = self.startOffset[i]
            self.table[i][1] = self.endOffset[i]
        return self.table
        
    
