#pragma once
#ifndef INDICATOR_CRT_SUMBARS_H_
#define INDICATOR_CRT_SUMBARS_H_

#include "CVAL.h"

namespace stradex {
    
Indicator stradex_API SUMBARS(double a);
Indicator stradex_API SUMBARS(const IndParam& a);

inline Indicator SUMBARS(const Indicator& ind, double a) {
    return SUMBARS(a)(ind);
}

inline Indicator SUMBARS(const Indicator& ind, const IndParam& a) {
    return SUMBARS(a)(ind);
}

inline Indicator SUMBARS(const Indicator& ind, const Indicator& a) {
    return SUMBARS(IndParam(a))(ind);
}

}  // namespace stradex

#endif
