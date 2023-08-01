#pragma once
#ifndef INDICATOR_CRT_HHVBARS_H_
#define INDICATOR_CRT_HHVBARS_H_

#include "../Indicator.h"

namespace stradex {

Indicator stradex_API HHVBARS(int n = 20);
Indicator stradex_API HHVBARS(const IndParam& n);

inline Indicator HHVBARS(const Indicator& ind, int n = 20) {
    return HHVBARS(n)(ind);
}

inline Indicator HHVBARS(const Indicator& ind, const IndParam& n) {
    return HHVBARS(n)(ind);
}

inline Indicator HHVBARS(const Indicator& ind, const Indicator& n) {
    return HHVBARS(IndParam(n))(ind);
}

}

#endif 
