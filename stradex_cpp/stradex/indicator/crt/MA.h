/*
 * MA.h
 *
 *  Created on: 2013-2-14
 *      Author: jialuechen
 */

#pragma once
#ifndef MA_H_
#define MA_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 简单移动平均
 * @param n 计算均值的周期窗口，n为0时从第一个有效数据开始计算
 * @ingroup Indicator
 */
Indicator stradex_API MA(int n = 22);
Indicator stradex_API MA(const IndParam& n);

/**
 * 简单移动平均
 * @param ind 待计算的数据
 * @param n 计算均值的周期窗口，n为0时从第一个有效数据开始计算
 * @ingroup Indicator
 */
inline Indicator stradex_API MA(const Indicator& ind, int n = 22) {
    return MA(n)(ind);
}

inline Indicator stradex_API MA(const Indicator& ind, const IndParam& n) {
    return MA(n)(ind);
}

inline Indicator MA(const Indicator& ind, const Indicator& n) {
    return MA(IndParam(n))(ind);
}

}  // namespace stradex

#endif /* MA_H_ */
