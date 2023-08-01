

#pragma once
#ifndef INDICATOR_CRT_EVERY_H_
#define INDICATOR_CRT_EVERY_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 一直存在
 * @details
 * <pre>
 * 用法：EVERY (X,N) 表示条件X在N周期一直存在
 * 例如：EVERY(CLOSE>OPEN,10) 表示前10日内一直是阳线
 * </pre>
 * @ingroup Indicator
 */
Indicator stradex_API EVERY(int n = 20);
Indicator stradex_API EVERY(const IndParam& n);

inline Indicator EVERY(const Indicator& ind, int n = 20) {
    return EVERY(n)(ind);
}

inline Indicator EVERY(const Indicator& ind, const IndParam& n) {
    return EVERY(n)(ind);
}

inline Indicator EVERY(const Indicator& ind, const Indicator& n) {
    return EVERY(IndParam(n))(ind);
}

}  // namespace stradex

#endif
