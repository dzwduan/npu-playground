from pymtl3 import *
from collections import deque
from copy import deepcopy
from sort import sort_fl

class SortUnitCL(Component):
    def construct(s, bits=8, nstages=3):
        s.in_val = InPort()
        s.in_ = [InPort(bits) for _ in range(4)]
        s.out_val = OutPort()
        s.out = [OutPort(bits) for _ in range(4)]
        s.pipe = deque([[0, 0, 0, 0, 0]] * (nstages - 1))

        @update_ff
        def block():
            s.pipe.append(deepcopy([s.in_val] + sort_fl(s.in_)))
            data = s.pipe.popleft()
            s.out_val <<= data[0]
      
            for i, v in enumerate(data[1:]):
                s.out[i] <<= v

    # 行跟踪（显示输入输出状态）    
            for i in range(nstages - 1):
                print(f"pipe = {s.pipe[i]}")


    # 行跟踪（显示输入输出状态）
    def line_trace(s):
        # 输入状态字符串
        in_str = '{' + ','.join(map(str, s.in_)) + '}'
        if not s.in_val:
            in_str = ' ' * len(in_str)

        # 输出状态字符串
        out_str = '{' + ','.join(map(str, s.out)) + '}'
        if not s.out_val:
            out_str = ' ' * len(out_str)

        # 返回格式化的输入输出状态
        return f"{in_str}|{out_str}"

from pymtl3.stdlib.test_utils import run_test_vector_sim  

# 测试函数：三阶段流水线
def test_3stage_stream(cmdline_opts):
    run_test_vector_sim(SortUnitCL(nstages=3), [
        ('in_val in_[0] in_[1] in_[2] in_[3] out_val out[0] out[1] out[2] out[3]*'),
        [ 1,      4,    2,    3,    1,    0,     0,     0,     0,     0       ],
        [ 0,      0,    0,    0,    0,    0,     0,     0,     0,     0       ],
        [ 0,      0,    0,    0,    0,    0,     0,     0,     0,     0       ],
        [ 0,      0,    0,    0,    0,    1,     1,     2,     3,     4       ],
    ], cmdline_opts)