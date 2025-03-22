from pymtl3 import *

from sys import argv
from pymtl3.stdlib.test_utils import config_model_with_cmdline_opts

class RegIncr(Component):
    def construct(s):
        s.in_ = InPort(Bits8)
        s.out = OutPort(Bits8)

        s.reg_out = Wire(Bits8)  # 内部信号，看起来只能够构造wire，然后update，作为寄存器

        # 每个时钟上升沿调用一次
        @update_ff
        def block1():
            if s.reset:
                s.reg_out <<= 0
            else:
                s.reg_out <<= s.in_

        # 组合逻辑
        @update
        def block2():
            s.out @= s.reg_out + 1


# # 从命令行获取输入值列表
# input_values = [int(x, 0) for x in argv[1:]]

# # 在输入值列表末尾添加三个零值，以便模拟多几个周期，方便观察输出
# input_values.extend([0] * 3)

# model = RegIncr()
# model.elaborate()

# # 应用默认的通用 Pass 组以添加模拟功能
# model.apply(DefaultPassGroup(textwave=True))

# # 重置模拟器
# model.sim_reset()

# # 输入值应用与输出值显示
# for input_value in input_values:
#     model.in_ @= input_value
#     model.sim_eval_combinational()
    
#     # 显示当前周期的输入与输出
#     print(f"cycle = {model.sim_cycle_count()}: in = {model.in_}, out = {model.out}")
    
#     # 模拟器前进一个周期
#     model.sim_tick()

# model.print_textwave()


def test_basic(cmdline_opts):
    model = RegIncr()
    model = config_model_with_cmdline_opts(model, cmdline_opts, duts=[])

    model.apply(DefaultPassGroup(linetrace=True))
    model.sim_reset()

    def t(in_, out):
        model.in_ @= in_
        model.sim_eval_combinational()

        if out != '?':
            assert model.out == out

        model.sim_tick()

    t(0x00, '?')
    t(0x13, 0x01)
    t(0x27, 0x14)
    t(0x00, 0x28)
    t(0x00, 0x01)
    t(0x00, 0x01)

from pymtl3.stdlib.test_utils import run_test_vector_sim
import random

# 测试小输入值
def test_small(cmdline_opts):
    run_test_vector_sim(RegIncr(), [
        # 输出端口使用*标识
        ('in_ out*'),
        [ 0x00, '?' ],   # 第一个周期，我们不关心输出
        [ 0x03, 0x01 ],  # 输入 0x03，期望输出 0x01（上个周期递增 1）
        [ 0x06, 0x04 ],  # 输入 0x06，期望输出 0x04
        [ 0x00, 0x07 ],  # 输入 0x00，期望输出 0x07
    ], cmdline_opts)

# 测试大输入值
def test_large(cmdline_opts):
    run_test_vector_sim(RegIncr(), [
        ('in_ out*'),
        [ 0xa0, '?' ],   # 输入较大值，第一周期不关心输出
        [ 0xb3, 0xa1 ],  # 输入 0xb3，期望输出 0xa1
        [ 0xc6, 0xb4 ],  # 输入 0xc6，期望输出 0xb4
        [ 0x00, 0xc7 ],  # 输入 0x00，期望输出 0xc7
    ], cmdline_opts)

# 测试溢出情况
def test_overflow(cmdline_opts):
    run_test_vector_sim(RegIncr(), [
        ('in_ out*'),
        [ 0x00, '?' ],   # 第一个周期，不关心输出
        [ 0xfe, 0x01 ],  # 输入 0xfe，期望输出 0x01（0xfe + 1 = 0xff，下一周期回到 0x01）
        [ 0xff, 0xff ],  # 输入 0xff，递增至溢出，保持 0xff
        [ 0x00, 0x00 ],  # 输入 0x00，重置输出为 0x00
    ], cmdline_opts)


def test_random(cmdline_opts):
    test_vector_table = [('in_', 'out*')]

    last_result = '?'

    for i in range(10):
        rand_val = b8(random.randint(0, 255))   
        test_vector_table.append([rand_val, last_result])
        last_result = b8(rand_val + 1, trunc_int=True)

    run_test_vector_sim(RegIncr(), test_vector_table, cmdline_opts)