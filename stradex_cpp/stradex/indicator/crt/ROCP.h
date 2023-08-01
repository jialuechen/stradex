

#pragma once
#ifndef INDICATOR_CRT_ROCP_H_
#define INDICATOR_CRT_ROCP_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 变动率指标 (price - prePrice) / prevPrice
 * @ingroup Indicator
 */
Indicator stradex_API ROCP(int n = 10);
Indicator stradex_API ROCP(const IndParam& n);

inline Indicator ROCP(const Indicator& ind, int n = 10) {
    return ROCP(n)(ind);
}

inline Indicator ROCP(const Indicator& ind, const IndParam& n) {
    return ROCP(n)(ind);
}

inline Indicator ROCP(const Indicator& ind, const Indicator& n) {
    return ROCP(IndParam(n))(ind);
}

}  // namespace stradex

#endif
