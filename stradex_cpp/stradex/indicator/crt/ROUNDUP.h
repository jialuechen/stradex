

#pragma once
#ifndef INDICATOR_CRT_ROUNDUP_H_
#define INDICATOR_CRT_ROUNDUP_H_

#include "CVAL.h"

namespace stradex {

/**
 * 向上截取，如10.1截取后为11
 * @ingroup Indicator
 */
Indicator stradex_API ROUNDUP(int ndigits = 2);
Indicator ROUNDUP(price_t, int ndigits = 2);
Indicator ROUNDUP(const Indicator& ind, int ndigits = 2);

inline Indicator ROUNDUP(const Indicator& ind, int n) {
    return ROUNDUP(n)(ind);
}

inline Indicator ROUNDUP(price_t val, int n) {
    return ROUNDUP(CVAL(val), n);
}

}  // namespace stradex

#endif
