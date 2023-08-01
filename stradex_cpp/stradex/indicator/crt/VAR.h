

#pragma once
#ifndef INDICATOR_CRT_VAR_H_
#define INDICATOR_CRT_VAR_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 计算N周期内估算样本方差
 * @param n N日时间窗口
 * @ingroup Indicator
 */
Indicator stradex_API VAR(int n = 10);
Indicator stradex_API VAR(const IndParam& n);

inline Indicator VAR(const Indicator& data, int n = 10) {
    return VAR(n)(data);
}

inline Indicator VAR(const Indicator& data, const IndParam& n) {
    return VAR(n)(data);
}

inline Indicator VAR(const Indicator& data, const Indicator& n) {
    return VAR(IndParam(n))(data);
}

}  // namespace stradex

#endif
