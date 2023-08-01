

#pragma once
#ifndef INDICATOR_CRT_ROCR_H_
#define INDICATOR_CRT_ROCR_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 变动率指标 (price / prevPrice)
 * @ingroup Indicator
 */
Indicator stradex_API ROCR(int n = 10);
Indicator stradex_API ROCR(const IndParam& n);

inline Indicator ROCR(const Indicator& ind, int n = 10) {
    return ROCR(n)(ind);
}

inline Indicator ROCR(const Indicator& ind, const IndParam& n) {
    return ROCR(n)(ind);
}

inline Indicator ROCR(const Indicator& ind, const Indicator& n) {
    return ROCR(IndParam(n))(ind);
}

}  // namespace stradex

#endif
