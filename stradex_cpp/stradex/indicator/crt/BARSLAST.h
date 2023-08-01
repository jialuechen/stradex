

#pragma once
#ifndef INDICATOR_CRT_BARSLAST_H_
#define INDICATOR_CRT_BARSLAST_H_

#include "CVAL.h"

namespace stradex {

/**
 * 上一次条件成立位置, 上一次条件成立到当前的周期数。
 * @details
 * <pre>
 * 用法：BARSLAST(X): 上一次 X 不为 0 到现在的天数。
 * 例如：BARSLAST(CLOSE/REF(CLOSE,1)>=1.1) 表示上一个涨停板到当前的周期数。
 * </pre>
 * @ingroup Indicator
 */
Indicator stradex_API BARSLAST();
Indicator BARSLAST(price_t);
Indicator BARSLAST(const Indicator& ind);

inline Indicator BARSLAST(const Indicator& ind) {
    return BARSLAST()(ind);
}

inline Indicator BARSLAST(price_t val) {
    return BARSLAST(CVAL(val));
}

}  // namespace stradex

#endif
