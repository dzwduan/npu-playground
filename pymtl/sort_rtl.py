from pymtl3 import *



class SortUnitFlatRTL(Component):

    def construct(s, nbits = 8):
        s.in_val = InPort()
        s.in_ = [InPort(nbits) for _ in range(4)]
        s.out_val = OutPort()
        s.out = [OutPort(nbits) for _ in range(4)]


        # s0 -> s1
        s.val_S1 = Wire()
        s.elem_S1 = [Wire(nbits) for _ in range(4)]

        @update_ff
        def pipereg_S02S1():
            if s.reset:
                s.val_S1 <<= 0
            else:
                s.val_S1 <<= s.in_val

            for i in range(4):
                s.elem_S1[i] <<= s.in_[i]

         
        # S1 组合逻辑
        s.elem_next_S1 = [Wire(nbits) for _ in range(4)]

        @update
        