/*
 * ABS.h
 *
 *  Created on: 2019-4-2
 *      Author: jialuechen
 */

#pragma once
#ifndef INDICATOR_CRT_ABS_H_
#define INDICATOR_CRT_ABS_H_

#include "CVAL.h"

namespace stradex {

/**
 * 求绝对值
 * @ingroup Indicator
 */
Indicator stradex_API ABS();
Indicator ABS(price_t);
Indicator ABS(const Indicator& ind);

inline Indicator ABS(const Indicator& ind) {
    return ABS()(ind);
}

inline Indicator ABS(price_t val) {
    return ABS(CVAL(val));
}

}  // namespace stradex

#endif /* INDICATOR_CRT_ABS_H_ */
