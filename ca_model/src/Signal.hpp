#include <functional>
#include <vector>
#include <cstdint>

// 信号类：支持自动连接与运算符重载
struct Signal {
    uint32_t value = 0;
    std::vector<Signal*> drivers; // 驱动此信号的其他信号

    // 连接运算符重载：a >> b 表示 a 驱动 b
    Signal& operator>>(Signal& rhs) { 
        rhs.drivers.push_back(this); 
        return rhs;
    }
};

// 模块基类
struct Module {
    // 输入/输出端口声明宏
    #define INPUT(name)  Signal& name = _port(true)
    #define OUTPUT(name) Signal& name = _port(false)

    // 模块逻辑定义接口
    template<typename F>
    Module(F logic) { logic(*this); }

    // 连接子模块端口：m.io >> sub.io
    template<typename T>
    void operator>>(T& sub) { /* 自动连接同名端口 */ }

private:
    std::vector<Signal> ports_;
    Signal& _port(bool is_input) { 
        ports_.emplace_back();
        return ports_.back();
    }
};