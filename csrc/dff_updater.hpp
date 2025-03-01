#pragma once
#include <vector>
#include "dff_base.hpp"

template<typename T>
class DFFUpdater {
private:
    std::vector<DffBase<T>*> dffs;
    bool global_rst_n;
    bool global_en;

public:
    DFFUpdater() : global_rst_n(true), global_en(true) {}

    // 注册DFF
    void register_dff(DffBase<T>* dff) {
        dffs.push_back(dff);
    }

    // 全局复位控制
    void global_reset(bool rst_val) {
        global_rst_n = !rst_val;
        for (auto dff : dffs) {
            dff->reset(rst_val);
        }
    }

    // 全局使能控制
    void global_enable(bool en_val) {
        global_en = en_val;
        for (auto dff : dffs) {
            dff->sete(en_val);
        }
    }

    // 全局时钟更新
    void global_clock() {
        for (auto dff : dffs) {
            dff->clock();
        }
    }

    // 获取注册的DFF数量
    size_t get_dff_count() const {
        return dffs.size();
    }

    // 清除所有注册的DFF
    void clear() {
        dffs.clear();
    }
};