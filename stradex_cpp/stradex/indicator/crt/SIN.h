

#pragma once
#ifndef INDICATOR_CRT_SIN_H_
#define INDICATOR_CRT_SIN_H_

#include "CVAL.h"

namespace stradex {

/**
 * 正弦值
 * @ingroup Indicator
 */
Indicator stradex_API SIN();
Indicator SIN(price_t);
Indicator SIN(const Indicator& ind);

inline Indicator SIN(const Indicator& ind) {
    return SIN()(ind);
}

inline Indicator SIN(price_t val) {
    return SIN(CVAL(val));
}

}  // namespace stradex

#endif
