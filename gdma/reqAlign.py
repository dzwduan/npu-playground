import pandas as pd
import numpy as np
import math
from math import *

# 向下取整
def align_floor(a, base):
    return math.floor(a / base) * base


# 向上取整
def align_ceil(a, base):
    return math.ceil(a / base) * base


class RdGmReq:
    def __init__(self, reqId: int, startAddr: int, length: int):
        self.reqId = reqId
        self.startAddr = startAddr
        self.length = length
        self.end_addr = self.startAddr + self.length
    
    def to_dict(self) -> dict:
        return {k: v for k, v in self.__dict__.items()}

    def __str__(self) -> str:
        return f"ReqId: {self.reqId:3}, StartAddr: {self.startAddr:3}, Length: {self.length}"
    
    def random_generate(start_addr, id_num, max_len):
        for i in range(id_num):
            random_len = 14
            start = start_addr + random_len * i
            length = min(random_len, max_len - i * random_len)
            yield RdGmReq(i, start, length)

# 理论上，我只需要知道start，Length, 就能的后所有的结果，因此需要对rdGmReq增加一个解析器
class AlignedRdGmReq:
    def __init__(self, req : list[RdGmReq], align_len: int):
        self.req = req
        self.align_len = align_len
        self.start, self.length = self.transform(req)
        self.start_addr = np.zeros((len(req),), dtype=int)
        self.start_offset = np.zeros((len(req),), dtype=int)
        self.end_offset = np.zeros((len(req),), dtype=int)

    # 解析器, 获取startAddr + total Length
    def transform(self, req: list[RdGmReq]) -> tuple:
        start_addr = req[0].startAddr
        length = sum([r.length for r in req])
        return start_addr, length

    def __str__(self) -> str:
        print("\n")
        str = "reqId\tstartAddr\tstartOffset\tendOffset\n"
        for i, req in enumerate(self.req):
            str += f"{req.reqId}\t{self.start_addr[i]}\t\t{self.start_offset[i]}\t\t{self.end_offset[i]}\n"
        return str

    # generaae align req from start_addr and length
    def alignReq(self):
        tmp_end = align_ceil(self.start, self.align_len)
        for i in range(len(self.req)):
            aligned_start_addr = align_floor(self.start + i*align_len, self.align_len)
            aligned_end_addr = align_ceil(self.start + i*align_len, self.align_len) if i!=0 else tmp_end
            self.start_addr[i] = aligned_start_addr
            self.start_offset[i] = 0 if i!=0 else self.start - aligned_start_addr
            self.end_offset[i] = min(aligned_end_addr -  self.start_addr[i], self.start + self.length- i*align_len) - 1

    
if __name__ == "__main__":
    # Generate a list of random requests
    reqs = list(RdGmReq.random_generate(4, 4, 49))
    for req in reqs:
        print(req)

    # Align the requests to a given length
    align_len = 16
    aligned_reqs = AlignedRdGmReq(reqs, align_len)
    print(aligned_reqs)
    aligned_reqs.alignReq()
    print(aligned_reqs)


#TODO: 1. 增加解析器，重构alignGdmaReq . finish
#TODO: 2. 需要和ub部分串起来