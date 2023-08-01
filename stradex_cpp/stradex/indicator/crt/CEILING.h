

#pragma once
#ifndef INDICATOR_CRT_CEIL_H_
#define INDICATOR_CRT_CEIL_H_

#include "CVAL.h"

namespace stradex {

/**
 * 向上舍入 (向数值增大方向舍入)
 * 用法：CEILING(A)返回沿A数值增大方向最接近的整数
 * 例如：CEILING(12.3)求得13；CEILING(-3.5)求得-3
 * @ingroup Indicator
 */
Indicator stradex_API CEILING();
Indicator CEILING(price_t);
Indicator CEILING(const Indicator& ind);

inline Indicator CEILING(const Indicator& ind) {
    return CEILING()(ind);
}

inline Indicator CEILING(price_t val) {
    return CEILING(CVAL(val));
}

}  // namespace stradex

#endif
