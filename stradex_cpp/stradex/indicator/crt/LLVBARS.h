

#pragma once
#ifndef INDICATOR_CRT_LLVBARS_H_
#define INDICATOR_CRT_LLVBARS_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 上一低点位置 求上一低点到当前的周期数。
 * @details
 * <pre>
 * 用法：LLVBARS(X,N):求N周期内X最低值到当前周期数N=0表示从第一个有效值开始统计
 * 例如：LLVBARS(HIGH,20)求得20日最低点到当前的周期数
 * </pre>
 * @ingroup Indicator
 */
Indicator stradex_API LLVBARS(int n = 20);
Indicator stradex_API LLVBARS(const IndParam& n);

inline Indicator LLVBARS(const Indicator& ind, int n = 20) {
    return LLVBARS(n)(ind);
}

inline Indicator LLVBARS(const Indicator& ind, const IndParam& n) {
    return LLVBARS(n)(ind);
}

inline Indicator LLVBARS(const Indicator& ind, const Indicator& n) {
    return LLVBARS(IndParam(n))(ind);
}

}  // namespace stradex

#endif
