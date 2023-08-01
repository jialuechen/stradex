#pragma once
#ifndef INDICATOR_CRT_FLOOR_H_
#define INDICATOR_CRT_FLOOR_H_

#include "CVAL.h"

namespace stradex {

Indicator stradex_API FLOOR();
Indicator FLOOR(price_t);
Indicator FLOOR(const Indicator& ind);

inline Indicator FLOOR(const Indicator& ind) {
    return FLOOR()(ind);
}

inline Indicator FLOOR(price_t val) {
    return FLOOR(CVAL(val));
}

}  

#endif 
