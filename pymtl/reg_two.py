from pymtl3 import *
from pymtl3.stdlib.test_utils import config_model_with_cmdline_opts
from pymtl3.passes.PassGroups import DefaultPassGroup


class RegIncr(Component):
    def construct(s):
        s.in_ = InPort(Bits8)
        s.out = OutPort(Bits8)

        s.reg_out = Wire(Bits8)

        @update_ff
        def ff_logic():
            if s.reset:
                s.reg_out <<= 0
            else:
                s.reg_out <<= s.in_

        @update
        def comb_logic():
            s.out @= s.reg_out + 1


class RegIncr2RegIncr(Component):
    def construct(s):
        s.in_ = InPort(Bits8)
        s.out = OutPort(Bits8)


        s.reg1 = RegIncr()
        s.reg2 = RegIncr()

        s.reg1.in_ //= s.in_
        s.reg2.in_ //= s.reg1.out
        s.out //= s.reg2.out


def basic_print(cmdline_opts):
    model = RegIncr2RegIncr()
    model.elaborate()
    model = config_model_with_cmdline_opts(model, cmdline_opts, duts=[])

    model.apply(DefaultPassGroup(textwave=True))

    model.sim_reset()

    input_vals = [1, 2, 3, 4, 5]

    for input_val in input_vals:
        model.in_ @= input_val
        model.sim_eval_combinational()

        print(f"cycle = {model.sim_cycle_count()}: in = {model.in_}, out = {model.out}")

        model.sim_tick()

    model.print_textwave()

basic_print([])