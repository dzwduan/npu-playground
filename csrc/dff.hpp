#include <iostream>
#include <type_traits>

template<typename T>
class DFF {
    static_assert(std::is_default_constructible<T>::value, 
                 "Type T must be default constructible");

    public:
        T data_d;
        T data_q;
        bool en;
        bool rst_n;  // 低电平有效复位

    public:
        DFF() : data_d(T{}), data_q(T{}), en(false), rst_n(true) {}
        
        DFF(const T& data) : data_d(data), data_q(data), en(false), rst_n(true) {}
        
        void reset(bool rst_val) {
            rst_n = !rst_val;  // 转换为低电平有效
            if (!rst_n) {
                data_q = T{};
            }
        }
        
        void sete(bool en_val) {
            en = en_val;
        }
        
        bool isEnabled() const {
            return en;
        }
        
        // set D端
        void set(const T& data) {
            if (en) {
                data_d = data;
            }
        }
        
        void clock() {
            if (!rst_n) {
                data_q = T{};
            }
            else if (en) {
                data_q = data_d;
            }
        }
        
        // 获取DFF的q端
        T get() const {
            return data_q;
        }

        // 获取DFF的d端
        T get_d() const {
            return data_d;
        }

        T operator + (const T& data) {
            return data_d + data;
        }

        T operator + (DFF<T>& other) {
            return data_d + other.get_d();
        }

        T operator - (const T& data) {
            return data_d - data;
        }

        T operator - (DFF<T>& other) {
            return data_d - other.get_d();
        }



        bool operator == (const T& data) {
            return data_d == data;
        }

        bool operator == (DFF<T>& other) {
            return data_d == other.get_d();
        }


        // like veilog reg <= data;
        DFF& operator <= (const T& data) {
            this->data_d = data;
            return *this;
        }

        DFF& operator <= (const DFF& other) {
            this->data_d = other.get_d();
            return *this;
        }
};