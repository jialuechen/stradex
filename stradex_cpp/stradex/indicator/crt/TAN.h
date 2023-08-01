

#pragma once
#ifndef INDICATOR_CRT_TAN_H_
#define INDICATOR_CRT_TAN_H_

#include "CVAL.h"

namespace stradex {

/**
 * 正切值
 * @ingroup Indicator
 */
Indicator stradex_API TAN();
Indicator TAN(price_t);
Indicator TAN(const Indicator& ind);

inline Indicator TAN(const Indicator& ind) {
    return TAN()(ind);
}

inline Indicator TAN(price_t val) {
    return TAN(CVAL(val));
}

}  // namespace stradex

#endif
