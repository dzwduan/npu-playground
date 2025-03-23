#pragma once 
#include <vector>

template <typename T>
class Wire {
    T value;
    std::vector<Wire*> listeners;  // 监听该Wire的所有下游Wire
public:
    Wire& operator = (const T& v) {  // 普通赋值
        value = v;
        return *this;
    }
    
    // 当连接赋值时建立监听关系
    Wire& operator = (Wire& src) {
        src.listeners.push_back(this); 
        this->value = src.value;
        return *this;
    }
    
    // 值更新时通知所有监听者
    void update(const T& new_val) {
        value = new_val;
        for (auto w : listeners) {
            w->update(value);
        }
    }
    
    operator T() const { return value; }
};