

#pragma once
#ifndef INDICATOR_CRT_ROUND_H_
#define INDICATOR_CRT_ROUND_H_

#include "CVAL.h"

namespace stradex {

/**
 * 四舍五入
 * @ingroup Indicator
 */
Indicator stradex_API ROUND(int ndigits = 2);
Indicator ROUND(price_t, int ndigits = 2);
Indicator ROUND(const Indicator& ind, int ndigits = 2);

inline Indicator ROUND(const Indicator& ind, int n) {
    return ROUND(n)(ind);
}

inline Indicator ROUND(price_t val, int n) {
    return ROUND(CVAL(val), n);
}

}  // namespace stradex

#endif
