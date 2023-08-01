

#pragma once
#ifndef INDICATOR_CRT_REVERSE_H_
#define INDICATOR_CRT_REVERSE_H_

#include "CVAL.h"

namespace stradex {

/**
 * 求相反数，REVERSE(X)返回-X
 * @ingroup Indicator
 */
Indicator stradex_API REVERSE();
Indicator REVERSE(price_t);
Indicator REVERSE(const Indicator& ind);

inline Indicator REVERSE(const Indicator& ind) {
    return REVERSE()(ind);
}

inline Indicator REVERSE(price_t val) {
    return REVERSE(CVAL(val));
}

}  // namespace stradex

#endif
