from typing import List, Dict
import numpy as np
from gm import *
from ub import *

# GDMA模块的设计，我暂时不切流水
class GDMA:
    def __init__(self, gm:GM, ub:UB, req: List[Dict[int, int]]):
        pass

    # 用rawRdGmReqGen保存生成的req，硬件上可能该模块就用于检查是否越界，是直接发给对齐模块的，软件上需要测试，所以单独加一下
    def rdGmReqGen(self, req: List[Dict[int, int]]):
        pass

    # 从rdGmReqGen中得到的 start + length, 根据GM的对齐需求生成startAddr, startOffset, endOffset
    def alignRdGmReqGen(self, start: int, length: int, align_len: int):
        pass

    # 记录alignRdGmReqGen生成的startOffset + endOffset + startAddr，可以理解为寄存器组
    def reqTable(self, startAddr : List[int], startOffset : List[int], endOffset : List[int], align_len: int):
        pass

    # 根据从reqTable返回的startOffset和endOffset + startAddr从GM中读取对应的data
    def rdData(self, startAddr: int, startOffset: int, endOffset: int):
        pass

    # 生成UB的写请求，但是需要考虑UB的位宽，这里UB每个bank 4Byte, 每次写入俩Bank, 产生的是id , validPixelPerId , 该请求需要考虑AlignedGmReq的length，并对齐到UB的宽度，再切分
    def wrUbReqGen(self, startAddr: int, length: int, align_len: int):
        pass

    # 每次从dataExtractor取validPixelPerReq个Byte，这里实际上就是用于补零
    def dataReader(self, validPixelPerReq: int):
        pass

    # 根据UB的布局，生成写入的数据格式，这里是2 bank，每个bank 4 Byte, 一次读一行validPixelPerReq
    def finalWrUbReqGen(self, validPixelPerId: int):
        pass

    # 写入UB
    def wrUb(self, startAddr: int, data: int):
        pass