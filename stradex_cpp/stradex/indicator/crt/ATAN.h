

#pragma once
#ifndef INDICATOR_CRT_ATAN_H_
#define INDICATOR_CRT_ATAN_H_

#include "CVAL.h"

namespace stradex {

/**
 * 反正切值
 * @ingroup Indicator
 */
Indicator stradex_API ATAN();
Indicator ATAN(price_t);
Indicator ATAN(const Indicator& ind);

inline Indicator ATAN(const Indicator& ind) {
    return ATAN()(ind);
}

inline Indicator ATAN(price_t val) {
    return ATAN(CVAL(val));
}

}  // namespace stradex

#endif
