

#pragma once
#ifndef INDICATOR_CRT_ACOS_H_
#define INDICATOR_CRT_ACOS_H_

#include "CVAL.h"

namespace stradex {

/**
 * 余弦值
 * @ingroup Indicator
 */
Indicator stradex_API ACOS();
Indicator ACOS(price_t);
Indicator ACOS(const Indicator& ind);

inline Indicator ACOS(const Indicator& ind) {
    return ACOS()(ind);
}

inline Indicator ACOS(price_t val) {
    return ACOS(CVAL(val));
}

}  // namespace stradex

#endif
