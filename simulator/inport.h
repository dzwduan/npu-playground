#pragma once

#include <string>
#include <unordered_map>
#include "port.h"

template <typename T>
class INPORT : public PortBase {
public:
    // 添加默认构造函数
    INPORT() : PortBase(""), value_(T{}) {}

    // 带名称构造函数
    explicit INPORT(const std::string& name) 
        : PortBase(name), value_(T{}) {}

    // 带值构造函数
    explicit INPORT(const T val)
        : PortBase(""), value_(val) {}

    // 统一使用基类名称存储
    const std::string& name() const override {
        return PortBase::name();  // 使用基类名称
    }

    operator T() const override {
        return value_;
    }

    INPORT& operator=(T val) override {
        value_ = val;
        return *this;
    }

private:
    T value_;
};