

#pragma once
#ifndef INDICATOR_CRT_ROCR100_H_
#define INDICATOR_CRT_ROCR100_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 变动率指标 (price / prevPrice) * 100
 * @ingroup Indicator
 */
Indicator stradex_API ROCR100(int n = 10);
Indicator stradex_API ROCR100(const IndParam& n);

inline Indicator ROCR100(const Indicator& ind, int n = 10) {
    return ROCR100(n)(ind);
}

inline Indicator ROCR100(const Indicator& ind, const IndParam& n) {
    return ROCR100(n)(ind);
}

inline Indicator ROCR100(const Indicator& ind, const Indicator& n) {
    return ROCR100(IndParam(n))(ind);
}

}  // namespace stradex

#endif
