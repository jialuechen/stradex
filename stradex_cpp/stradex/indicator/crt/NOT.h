/*
 * NOT.h
 *
 *  Created on: 2019-4-2
 *      Author: jialuechen
 */

#pragma once
#ifndef INDICATOR_CRT_NOT_H_
#define INDICATOR_CRT_NOT_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 求逻辑非。NOT(X)返回非X,即当X=0时返回1，否则返回0。
 * @ingroup Indicator
 */
Indicator stradex_API NOT();

/**
 * 求逻辑非。NOT(X)返回非X,即当X=0时返回1，否则返回0。
 * @param ind 待计算的数据
 * @ingroup Indicator
 */
Indicator NOT(const Indicator& ind);

inline Indicator NOT(const Indicator& ind) {
    return NOT()(ind);
}

}  // namespace stradex

#endif /* INDICATOR_CRT_NOT_H_ */
