

#pragma once
#ifndef INDICATOR_CRT_SQRT_H_
#define INDICATOR_CRT_SQRT_H_

#include "CVAL.h"

namespace stradex {

/**
 * 开平方
 * @details
 * <pre>
 * 用法：SQRT(X)为X的平方根
 * 例如：SQRT(CLOSE)收盘价的平方根
 * </pre>
 * @ingroup Indicator
 */
Indicator stradex_API SQRT();
Indicator SQRT(price_t);
Indicator SQRT(const Indicator& ind);

inline Indicator SQRT(const Indicator& ind) {
    return SQRT()(ind);
}

inline Indicator SQRT(price_t val) {
    return SQRT(CVAL(val));
}

}  // namespace stradex

#endif
