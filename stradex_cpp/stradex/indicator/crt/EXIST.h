

#pragma once
#ifndef INDICATOR_CRT_EXIST_H_
#define INDICATOR_CRT_EXIST_H_

#include "../Indicator.h"

namespace stradex {

Indicator stradex_API EXIST(int n = 20);
Indicator stradex_API EXIST(const IndParam& n);

inline Indicator EXIST(const Indicator& ind, int n = 20) {
    return EXIST(n)(ind);
}

inline Indicator EXIST(const Indicator& ind, const IndParam& n) {
    return EXIST(n)(ind);
}

inline Indicator EXIST(const Indicator& ind, const Indicator& n) {
    return EXIST(IndParam(n))(ind);
}

}  

#endif
