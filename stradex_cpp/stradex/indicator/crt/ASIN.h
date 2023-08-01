

#pragma once
#ifndef INDICATOR_CRT_ASIN_H_
#define INDICATOR_CRT_ASIN_H_

#include "CVAL.h"

namespace stradex {

/**
 * 反正弦值
 * @ingroup Indicator
 */
Indicator stradex_API ASIN();
Indicator ASIN(price_t);
Indicator ASIN(const Indicator& ind);

inline Indicator ASIN(const Indicator& ind) {
    return ASIN()(ind);
}

inline Indicator ASIN(price_t val) {
    return ASIN(CVAL(val));
}

}  // namespace stradex

#endif
