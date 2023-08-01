/*
 * STD.h
 *
 *  Created on: 2013-4-18
 *      Author: jialuechen
 */

#pragma once
#ifndef STD_H_
#define STD_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 计算N周期内样本标准差
 * @param n N日时间窗口
 * @ingroup Indicator
 */
Indicator stradex_API STDEV(int n = 10);
Indicator stradex_API STDEV(const IndParam& n);

/**
 * 计算N周期内样本标准差
 * @param data 输入数据，单一输入
 * @param n N日时间窗口
 * @ingroup Indicator
 */
inline Indicator stradex_API STDEV(const Indicator& data, int n = 10) {
    return STDEV(n)(data);
}

inline Indicator stradex_API STDEV(const Indicator& data, const IndParam& n) {
    return STDEV(n)(data);
}

inline Indicator stradex_API STDEV(const Indicator& data, const Indicator& n) {
    return STDEV(IndParam(n))(data);
}

}  // namespace stradex

#endif /* STD_H_ */
