/*
 * COUNT.h
 *
 *  Created on: 2019-3-25
 *      Author: jialuechen
 */

#pragma once
#ifndef COUNT_H_
#define COUNT_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 统计总数 统计满足条件的周期数。
 * @details
 * <pre>
 * 用法：COUNT(X,N),统计N周期中满足X条件的周期数,若N=0则从第一个有效值开始。
 * 例如：COUNT(CLOSE>OPEN,20)表示统计20周期内收阳的周期数
 * </pre>
 * @param n 周期数
 * @ingroup Indicator
 */
Indicator stradex_API COUNT(int n = 20);
Indicator stradex_API COUNT(const IndParam& n);

/**
 * 统计总数 统计满足条件的周期数。
 * @details
 * <pre>
 * 用法：COUNT(X,N),统计N周期中满足X条件的周期数,若N=0则从第一个有效值开始。
 * 例如：COUNT(CLOSE>OPEN,20)表示统计20周期内收阳的周期数
 * </pre>
 * @param ind 待统计指标
 * @param n 周期数
 * @ingroup Indicator
 */
inline Indicator stradex_API COUNT(const Indicator& ind, int n = 20) {
    return COUNT(n)(ind);
}

inline Indicator stradex_API COUNT(const Indicator& ind, const IndParam& n) {
    return COUNT(n)(ind);
}

inline Indicator stradex_API COUNT(const Indicator& ind, const Indicator& n) {
    return COUNT(IndParam(n))(ind);
}

}  // namespace stradex

#endif /* CVAL_H_ */
