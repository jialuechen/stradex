

#pragma once
#ifndef INDICATOR_CRT_VARP_H_
#define INDICATOR_CRT_VARP_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 计算N周期内总体样本方差
 * @param n N日时间窗口
 * @ingroup Indicator
 */
Indicator stradex_API VARP(int n = 10);
Indicator stradex_API VARP(const IndParam& n);

inline Indicator VARP(const Indicator& data, int n = 10) {
    return VARP(n)(data);
}

inline Indicator VARP(const Indicator& data, const IndParam& n) {
    return VARP(n)(data);
}

inline Indicator VARP(const Indicator& data, const Indicator& n) {
    return VARP(IndParam(n))(data);
}

}  // namespace stradex

#endif
