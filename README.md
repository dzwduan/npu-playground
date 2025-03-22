# NPU Playground

记录一下学习过程中的demo, 不一定能跑, 最终目标可能是一个周期精确的npu simulator, 测试基本靠AI随缘生成

2025.3.2: 本打算手写一个简单的cycle accurate建模框架，搜了一下有一大把，还是先做功能性的建模，[找到的py hdl](https://www.reddit.com/r/FPGA/comments/w7ut22/choice_of_python_hdl_library/) , 从解决问题的角度而言, 我只需要挑选最快实现的方式，而非性能最好的。

2025.3.5: 关于im2col对于带宽的影响 https://zhuanlan.zhihu.com/p/26647725429


## 如何快速出原型
1. 考虑使用pymtl3, 比systemc快
1. 参考 https://www.csl.cornell.edu/pymtl2019/
1. 参考 https://albertc9.github.io/2024/11/07/introduction-to-pymtl-basics/
1. 使用pymtl3 实现 gemmini的mesh tile pe层级的ca model
1. TODO: 深入理解 pymtl gcd and sort

## implement fifo lists:

1. sync fifo
1. async fifo
1. ping pong fifo
1. conflict-free fifo
1. buffets fifo


## implement systolic array :

1. Weight Stationary
1. Output Stationary

