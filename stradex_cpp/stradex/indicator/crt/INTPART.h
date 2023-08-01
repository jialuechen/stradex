

#pragma once
#ifndef INDICATOR_CRT_INTPART_H_
#define INDICATOR_CRT_INTPART_H_

#include "CVAL.h"

namespace stradex {

Indicator stradex_API INTPART();
Indicator INTPART(price_t);
Indicator INTPART(const Indicator& ind);

inline Indicator INTPART(const Indicator& ind) {
    return INTPART()(ind);
}

inline Indicator INTPART(price_t val) {
    return INTPART(CVAL(val));
}

}  // namespace stradex

#endif
