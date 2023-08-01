/*
 * EXP.h
 *
 *  Created on: 2019-4-3
 *      Author: jialuechen
 */

#pragma once
#ifndef INDICATOR_CRT_EXP_H_
#define INDICATOR_CRT_EXP_H_

#include "CVAL.h"

namespace stradex {

/**
 * 指数, EXP(X)为e的X次幂
 * @ingroup Indicator
 */
Indicator stradex_API EXP();
Indicator EXP(price_t);
Indicator EXP(const Indicator& ind);

inline Indicator EXP(const Indicator& ind) {
    return EXP()(ind);
}

inline Indicator EXP(price_t val) {
    return EXP(CVAL(val));
}

}  // namespace stradex

#endif /* INDICATOR_CRT_EXP_H_ */
