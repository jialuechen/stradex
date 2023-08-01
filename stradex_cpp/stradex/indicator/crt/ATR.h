/*
 * ATR.h
 *
 *  Created on: 2016年5月4日
 *      Author: Administrator
 */

#pragma once
#ifndef INDICATOR_CRT_ATR_H_
#define INDICATOR_CRT_ATR_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 平均真实波幅(Average True Range)
 * @param n 计算均值的周期窗口，必须为大于1的整数
 * @ingroup Indicator
 */
Indicator stradex_API ATR(int n = 14);
Indicator stradex_API ATR(const IndParam& n);

/**
 * 平均真实波幅(Average True Range)
 * @param data 待计算的源数据
 * @param n 计算均值的周期窗口，必须为大于1的整数
 * @ingroup Indicator
 */
inline Indicator stradex_API ATR(const Indicator& data, int n = 14) {
    return ATR(n)(data);
}

inline Indicator stradex_API ATR(const Indicator& data, const IndParam& n) {
    return ATR(n)(data);
}

inline Indicator stradex_API ATR(const Indicator& data, const Indicator& n) {
    return ATR(IndParam(n))(data);
}

}  // namespace stradex

#endif /* INDICATOR_CRT_ATR_H_ */
