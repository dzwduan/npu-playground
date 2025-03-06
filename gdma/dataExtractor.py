import numpy as np
from reqTable import *
from gm import *

# 根据reqTable返回的startOffset + endOffset，从GM中获取到对应的数据
# reqTable返回的是多行startoffset + endoffset, 每一行对一个一个entry？
class dataExtractor:
    def __init__(self, gm: np.ndarray, req_num):
        self.gm = gm
        self.data = np.zeros((req_num), dtype=int)

    def extract_data(self, startAddr, startOfset, endOffset):

