#pragma once

#include <functional>
#include <ostream>
#include <unordered_set>

class RegBase {
    protected:
    static std::unordered_set<RegBase *> all_regs;

public:
virtual ~RegBase() = default;
  virtual void update() = 0;
  static void global_clock() {
    for (auto &reg : all_regs)
      reg->update();
  }
};

// 在类外定义静态成员（C++17 起可用 inline 避免多定义问题）
inline std::unordered_set<RegBase*> RegBase::all_regs;

template <typename T> class Reg : public RegBase {
  T current_val;
  T next_val;
  bool updated = false;

public:
  Reg(T init) : current_val(init), next_val(init) { all_regs.insert(this); }
  ~Reg() {
    all_regs.erase(this);
  }
  // 禁用拷贝
  Reg(const Reg &) = delete;
  Reg &operator=(const Reg &) = delete;
  // 禁用移动
  Reg(Reg &&) = delete;
  Reg &operator=(Reg &&) = delete;

  void operator<<=(T new_val) {
    next_val = new_val;
    updated = true;
  }

  void update() override {
    if (updated) {
      current_val = next_val;
      updated = false;
    }
  }

  operator T() const { return current_val; }

  // 类型别名增强可读性
  using value_type = T;

  // 等于运算符（支持T和Reg<T>比较）
  bool operator==(const T &other) const noexcept {
    return current_val == other;
  }

  bool operator==(const Reg<T> &other) const noexcept {
    return current_val == other.current_val;
  }

  // 不等于运算符（通过等于运算符实现）
  bool operator!=(const T &other) const noexcept { return !(*this == other); }

  bool operator!=(const Reg<T> &other) const noexcept {
    return !(*this == other);
  }

  // 允许与派生类比较（可选）
  template <typename U>
  bool operator==(const Reg<U> &other) const noexcept
    requires(std::is_convertible_v<U, T>)
  {
    return current_val == static_cast<T>(other);
  }

  // 类型安全的全局比较运算符
  friend bool operator==(const T &lhs, const Reg<T> &rhs) noexcept {
    return rhs == lhs; // 复用成员函数
  }

  friend bool operator!=(const T &lhs, const Reg<T> &rhs) noexcept {
    return rhs != lhs;
  }

  // 仅用于初始化
  Reg& operator=(const T val) noexcept {
    if (current_val != val) {
      current_val = val;
    }
    return *this;
  }

  // implement fmt::printf for Reg
    friend std::ostream &operator<<(std::ostream &os, const Reg<T> &reg) {
        return os << reg.current_val;
    }
  // support for fmt::printf
  friend T get_value(const Reg<T> &reg) {
    return reg.current_val;
  }
};