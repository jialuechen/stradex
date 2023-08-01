

#pragma once
#ifndef INDICATOR_CRT_POW_H_
#define INDICATOR_CRT_POW_H_

#include "CVAL.h"

namespace stradex {

/**
 * 乘幂
 * @details
 * <pre>
 * 用法：POW(A,B)返回A的B次幂
 * 例如：POW(CLOSE,3)求得收盘价的3次方
 * </pre>
 * @ingroup Indicator
 */
Indicator stradex_API POW(int n);
Indicator stradex_API POW(const IndParam& n);

inline Indicator POW(const Indicator& ind, int n) {
    return POW(n)(ind);
}

inline Indicator POW(const Indicator& ind, const IndParam& n) {
    return POW(n)(ind);
}

inline Indicator POW(const Indicator& ind, const Indicator& n) {
    return POW(IndParam(n))(ind);
}

inline Indicator POW(price_t val, int n) {
    return POW(CVAL(val), n);
}

}  // namespace stradex

#endif
