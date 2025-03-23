#pragma once

#include <string>
#include <unordered_map>

class PortBase {

public:
    // 隐式类型转换
    virtual operator int() const = 0;
    
    // 赋值运算符
    virtual PortBase& operator=(int val) = 0;
    
    explicit PortBase(const std::string& name) : name_(name) {}
    virtual const std::string& name() const { return name_; }
    
    virtual ~PortBase() = default;

protected:
    std::string name_;
    
};