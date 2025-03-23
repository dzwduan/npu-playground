#pragma  once

#include <type_traits>
#include <vector>
#include <memory>


// D -> DFF -> Q flip-flop
template<typename T>
class DffBase {
    static_assert(std::is_default_constructible<T>::value, 
                 "Type T must be default constructible");

    private:
        T data_d;
        T data_q;
        bool rst_n;  // 低电平有效复位

    protected:
        static std::vector<DffBase<T> *> dff_list;

    

    public:
        DffBase() : data_d(T{}), data_q(T{}), rst_n(true) {
            dff_list.emplace_back(this);
        }
        
        DffBase(const T& data) : data_d(data), data_q(data), rst_n(true) {
            dff_list.emplace_back(this);
        }

        ~DffBase() {
            dff_list.erase(this);
        }
        
        void reset(bool rst_val) {
            rst_n = !rst_val;  // 转换为低电平有效
            if (!rst_n) {
                data_q = T{};
            }
        }
        
        // set D端
        void set(const T& data) {
            data_d = data;
        }
        
        void clock() {
            if (!rst_n) {
                data_q = T{};
            }
                
            else data_q = data_d;
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

        T operator + (DffBase<T>& other) {
            return data_d + other.get_d();
        }

        T operator - (const T& data) {
            return data_d - data;
        }

        T operator - (DffBase<T>& other) {
            return data_d - other.get_d();
        }



        bool operator == (const T& data) {
            return data_d == data;
        }

        bool operator == (DffBase<T>& other) {
            return data_d == other.get_d();
        }


        // like veilog reg <= data;
        DffBase& operator <<= (const T& data) {
            this->data_d = data;
            return *this;
        }

        DffBase& operator <<= (const DffBase& other) {
            this->data_d = other.get_d();
            return *this;
        }


        static void global_reset(bool rst_val) {
            for (auto dff : dff_list) {
                dff->reset(rst_val);
            }
        }

        static void global_clock() {
            for (auto dff : dff_list) {
                dff->clock();
            }
        }

        size_t get_dff_count() {
            return dff_list.size();
        }

        // auto clean up expired DFFs
        // void purge_expired() noexcept {
        //     dff_list.erase(
        //         std::__remove_if(dff_list.begin(), dff_list.end(),
        //             [](const auto& wp){ return wp.expired(); }),
        //         dff_list.end());
        // }
};

template <typename T>
class Dff : public DffBase<T> {
    public:
        Dff() : DffBase<T>() {}
        Dff(const T& data) : DffBase<T>(data) {}
};