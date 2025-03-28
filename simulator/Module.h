// Module.h 修改内容
#pragma once
#include "INPUT.h"
#include <string>
#include <unordered_map>

class Module {
  std::unordered_map<std::string, void *> inputs;
  std::string module_name;

protected:
  // 输入端口代理
  template <typename T> friend class INPUT;

  // 输出端口代理

  // 注册输入端口

  template <typename T>
  void register_input(const std::string &port_name, INPUT<T> &port) {
    inputs[port_name] = &port;
  }

public:
  Module(const std::string &name) : module_name(name) {
    ModuleContext::current_module = this;
  }

  // 自动生成端口全名
  static std::string gen_port_name(const char *port) {
    return std::string(ModuleContext::current_module->module_name) + "_in_" +
           port;
  }
    // 模块连接运算符
    void operator/=(Module& other) {
        for (auto& [name, ptr] : inputs) {
            if (other.inputs.count(name)) {
                // 类型安全的值拷贝
                auto src = static_cast<decltype(ptr)>(ptr);
                auto dst = static_cast<decltype(src)>(other.inputs[name]);
                *dst = *src;
            }
        }
    }

};