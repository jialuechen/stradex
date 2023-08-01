

#pragma once
#ifndef INDICATOR_CRT_AVEDEV_H_
#define INDICATOR_CRT_AVEDEV_H_

#include "MA.h"
#include "ABS.h"

namespace stradex {

/**
 * 平均绝对偏差，求X的N日平均绝对偏差
 * @param ind 待计算的数据
 * @param n 时间窗口
 * @ingroup Indicator
 */
inline Indicator AVEDEV(const Indicator& ind, int n = 22) {
    Indicator result = ABS(ind - MA(ind, n)) / n;
    result.name("AVEDEV");
    return result;
}

inline Indicator AVEDEV(const Indicator& ind, const Indicator& n) {
    Indicator result = ABS(ind - MA(ind, n)) / n;
    result.name("AVEDEV");
    return result;
}

inline Indicator AVEDEV(const Indicator& ind, const IndParam& n) {
    Indicator result = ABS(ind - MA(ind, n)) / n.get();
    result.name("AVEDEV");
    return result;
}

}  // namespace stradex

#endif
