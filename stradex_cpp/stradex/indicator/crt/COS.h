

#pragma once
#ifndef INDICATOR_CRT_COS_H_
#define INDICATOR_CRT_COS_H_

#include "CVAL.h"

namespace stradex {

/**
 * 余弦值
 * @ingroup Indicator
 */
Indicator stradex_API COS();
Indicator COS(price_t);
Indicator COS(const Indicator& ind);

inline Indicator COS(const Indicator& ind) {
    return COS()(ind);
}

inline Indicator COS(price_t val) {
    return COS(CVAL(val));
}

}  // namespace stradex

#endif
