from typing import List, Dict
import numpy as np
from gm import *
from ub import *
from reqAlign import *
from reqTable import *
from dataExtractor import *
from dataReader import *
from finalWrUbReq import *


# GDMA模块的设计，我暂时不切流水
class GDMA:
    def __init__(self, gm:GM, ub:UB):
        self.gm_align_len = 0
        self.ub_align_len = 0
        self.gm = gm
        self.ub = ub
        self.req = []
        self.test_num = 4
        self.test_start = 4
        self.test_len = 49

    # 用rawRdGmReqGen保存生成的req，硬件上可能该模块就用于检查是否越界，是直接发给对齐模块的，软件上需要测试，所以单独加一下
    # 得到了一系列错乱的请求，然后生成start_addr + length 发给aligned模块
    def rdGmReqGen(self):
        reqs = List(RdGmReq.random_generate(self.test_start, self.test_num, self.test_len))
        print(reqs)
        req_total_len = 0
        start = self.test_start
        for i in range(reqs):
            req_total_len += reqs[i].length
        return (start, req_total_len)

    # 从rdGmReqGen中得到的 start + length, 根据GM的对齐需求生成startAddr, startOffset, endOffset
    def alignRdGmReqGen(self, start: int, total_len: int, align_len: int):
        # start, req_total_len = self.rdGmReqGen()
        # align_len = self.gm_align_len
        startAddr, startOffset, endOffset = AlignedRdGmReq.alignReq(start, total_len, align_len)
        return (startAddr, startOffset, endOffset)

    # 记录alignRdGmReqGen生成的startOffset + endOffset + startAddr，可以理解为寄存器组
    def reqTable(self, startAddr : List[int], startOffset : List[int], endOffset : List[int], align_len: int):
        tableLen = len(startAddr)
        reqTable = ReqTable(tableLen).generate(startAddr, startOffset, endOffset)
        return reqTable


    # 根据从reqTable返回的startOffset和endOffset + startAddr从GM中读取对应的data
    def extractData(self, startAddr: int, startOffset: int, endOffset: int):
        

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