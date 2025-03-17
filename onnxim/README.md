# Cycle Accurate Systolic Array Simulator

1. 读Paper了解设计思路 -> Gemmini ISA
1. 了解Gemmini架构
1. 分析模拟器的运行流程 (conan版本问题，暂时没跑起来)
1. 本质上是给Gemmini写一个cycle Accurate的model，然后在这个基础上重构Gemmini
1. transformer并不适用于当前的Gemmini架构，利用率低于1%，本质上CNN和Transformer有冲突

## 目录说明
1. model 存放模型保存的数据
1. sripts 存放导onnx的脚本
1. src 依托都放里面


## 工具类
1. vscode onnx_viewer
1. miniconda
1. [.clangd配置](https://tonixwd.github.io/2024/10/08/%E5%AE%9E%E7%94%A8%E5%B7%A5%E5%85%B7%E7%AC%94%E8%AE%B0/clangd%E9%85%8D%E7%BD%AE%E6%96%87%E4%BB%B6%E7%AE%80%E4%BB%8B/)
1. [ONNX入门](https://zhuanlan.zhihu.com/p/346511883)
1. [docker mirror](https://tools.opsnote.top/registry-mirrors/)
