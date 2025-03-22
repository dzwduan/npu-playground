#include <memory>
#include "dff_base.hpp"

// implement cycle accurate circular fifo by using DffBase
// like fifo use rptr wptr, ren, wen, empty, full
template<typename T>
class circular_fifo {
protected:
    std::unique_ptr<DffBase<T>[]> data;
    int size;
    DffBase<int> count;
    DffBase<int> rptr;
    DffBase<int> wptr;
    DffBase<bool> ren;
    DffBase<bool> wen;
    DffBase<bool> empty;
    DffBase<bool> full;

public:
    circular_fifo(int size) : size(size), count(0) {
        data = std::make_unique<DffBase<T>[]>(size);
        rptr <= 0;
        wptr <= 0;
        ren <= false;
        wen <= false;
        empty <= true;
        full <= false;
    }

    bool canWrite() {
        return !full.get() & wen.get();
    }

    bool canRead() {
        return !empty.get() & ren.get() & (!wen.get() & (rptr.get() != wptr.get()));
    }

    void push(const T& val) {
        if (canWrite()) {
            data[wptr]  <= val;
            wptr        <= (wptr + 1) % size;
            count      <= count + 1;
        }
    }

    void pop(T& val) {
        if (canRead()) {
            val = data[rptr].get();
            rptr <= (rptr + 1) % size;
            count <= count - 1;
        }
    }



    T front() const {
        return data[rptr.get()];
    }

    T back() const {
        return data[(wptr.get() - 1 + size) % size];
    }

    int get_count() const {
        return count.get();
    }

    bool is_empty() {
        empty <<= (rptr == wptr);
        return empty.get();
    }

    bool is_full()  {
        full <<= ((wptr + 1) % size == rptr.get_d());
        return full.get();
    }

    void clock() {
        if (ren.get()) {
            if (rptr.get() == wptr.get()) {
                empty.set(true);
            }
            else {
                empty.set(false);
            }
        }
        if (wen.get()) {
            if ((wptr.get() + 1) % size == rptr.get()) {
                full.set(true);
            }
            else {
                full.set(false);
            }
        }
        if (ren.get() && !empty.get()) {
            rptr.clock();
        }
        if (wen.get() && !full.get()) {
            wptr.clock();
        }
        ren.clock();
        wen.clock();
        empty.clock();
        full.clock();
    }
};