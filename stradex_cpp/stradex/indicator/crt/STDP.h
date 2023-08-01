/*
 * STD.h
 *
 *  Created on: 2013-4-18
 *      Author: jialuechen
 */

#pragma once
#ifndef INDICATOR_CRT_STDP_H_
#define INDICATOR_CRT_STDP_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 计算N周期内总体标准差
 * @param n N日时间窗口
 * @ingroup Indicator
 */
Indicator stradex_API STDP(int n = 10);
Indicator stradex_API STDP(const IndParam& n);

inline Indicator STDP(const Indicator& data, int n = 10) {
    return STDP(n)(data);
}

inline Indicator STDP(const Indicator& data, const IndParam& n) {
    return STDP(n)(data);
}

inline Indicator STDP(const Indicator& data, const Indicator& n) {
    return STDP(IndParam(n))(data);
}

}  // namespace stradex

#endif /* INDICATOR_CRT_STDP_H_ */
