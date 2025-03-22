from pymtl3 import *


def sort_fl(arr):
    return sorted(arr)


class sortUnitFL(Component):
    def construct(s, nbits = 8):
        s.in_ = [InPort(nbits) for _ in range(4)]
        s.in_valid = InPort()

        s.out_valid = OutPort()
        s.out = [OutPort(nbits) for _ in range(4)]

        @update_ff
        def logic_ff():
            s.out_valid <<= s.in_valid
            for i, v in enumerate(sort_fl(s.in_)):
                s.out[i] <<= v

    # 行跟踪（显示输入输出状态）
    def line_trace(s):
        # 输入状态字符串
        in_str = '{' + ','.join(map(str, s.in_)) + '}'
        if not s.in_valid:
            in_str = ' ' * len(in_str)

        # 输出状态字符串
        out_str = '{' + ','.join(map(str, s.out)) + '}'
        if not s.out_valid:
            out_str = ' ' * len(out_str)

        # 返回格式化的输入输出状态
        return f"{in_str}|{out_str}"
    
from pymtl3.stdlib.test_utils import run_test_vector_sim

def test_basic():
    run_test_vector_sim(sortUnitFL(), [
        ('in_valid in_[0] in_[1] in_[2] in_[3] out_valid out[0] out[1] out[2] out[3]*'),
        # 复位周期：无输入，无输出
        [ 0,       0,     0,    0,    0,    0,     0,     0,     0,     0       ],
        # 第一个输入周期：输入有效，等待排序结果
        [ 1,       8,     3,    5,    1,    0,     0,     0,     0,     0       ],
        # 输出周期：输出排序结果
        [ 0,       0,     0,    0,    0,    1,     1,     3,     5,     8       ],
    ], cmdline_opts=[])