

#pragma once
#ifndef INDICATOR_CRT_DEVSQ_H_
#define INDICATOR_CRT_DEVSQ_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 数据偏差平方和，求X的N日数据偏差平方和
 * @param n N日时间窗口
 * @ingroup Indicator
 */
Indicator stradex_API DEVSQ(int n = 10);
Indicator stradex_API DEVSQ(const IndParam& n);

inline Indicator DEVSQ(const Indicator& data, int n = 10) {
    return DEVSQ(n)(data);
}

inline Indicator DEVSQ(const Indicator& data, const IndParam& n) {
    return DEVSQ(n)(data);
}

inline Indicator DEVSQ(const Indicator& data, const Indicator& n) {
    return DEVSQ(IndParam(n))(data);
}

}  // namespace stradex

#endif
