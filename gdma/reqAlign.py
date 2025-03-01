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

    def end_addr(self) -> int:
        return self.startAddr + self.length
    
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


if __name__ == "__main__":
    # Generate a list of random requests
    reqs = list(RdGmReq.random_generate(4, 4, 49))
    for req in reqs:
        print(req)
