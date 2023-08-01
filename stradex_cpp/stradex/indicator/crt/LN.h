/*
 * LN.h
 *
 *  Created on: 2019-4-11
 *      Author: jialuechen
 */

#pragma once
#ifndef INDICATOR_CRT_LN_H_
#define INDICATOR_CRT_LN_H_

#include "CVAL.h"

namespace stradex {

/**
 * 求自然对数
 * 用法：LN(X)以e为底的对数
 * 例如：LN(CLOSE)求收盘价的对数
 * @ingroup Indicator
 */
Indicator stradex_API LN();
Indicator LN(price_t);
Indicator LN(const Indicator& ind);

inline Indicator LN(const Indicator& ind) {
    return LN()(ind);
}

inline Indicator LN(price_t val) {
    return LN(CVAL(val));
}

}  // namespace stradex

#endif /* INDICATOR_CRT_LN_H_ */
