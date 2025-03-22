from pymtl3 import *

def checksum( words ):
    sum1 = b32(0)
    sum2 = b32(0)

    for word in words:
        sum1 = (sum1 + word)&0xffff
        sum2 = (sum2 + sum1)&0xffff
    return (sum2 << 16) | sum1