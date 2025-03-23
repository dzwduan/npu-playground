#pragma once


#include <string>
#include <unordered_map>
#include "port.h"

template <typename T>
class OUTPORT : public PortBase {
public:
    // 添加默认构造函数
    OUTPORT() : PortBase(""), value_(T{}) {}

    // 带名称构造函数
    explicit OUTPORT(const std::string& name) 
        : PortBase(name), value_(T{}) {}

    // 带值构造函数
    explicit OUTPORT(const T val)
        : PortBase(""), value_(val) {}

    // 统一使用基类名称存储
    const std::string& name() const override {
        return PortBase::name();  // 使用基类名称
    }

    operator T() const override {
        return value_;
    }

    OUTPORT& operator=(T val) override {
        value_ = val;
        return *this;
    }

private:
    T value_;
};