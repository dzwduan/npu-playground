import numpy as np
from reqTable import *
from gm import *

# 根据reqTable返回的startOffset + endOffset，从GM中获取到对应的数据
# reqTable返回的是多行startoffset + endoffset, 每一行对一个一个entry？
class dataExtractor:
    def __init__(self, gm: np.ndarray, req_table: reqTable):
        self.gm = gm
        self.req_table = req_table
        self.data = np.zeros((len(req_table.reqId),), dtype=int)

    def extract_data(self):
        for i in range(len(self.req_table.reqId)):
            start = self.req_table.startOffset[i]
            end = self.req_table.endOffset[i]
            self.data[i] = self.gm[start][end]
        return self.data