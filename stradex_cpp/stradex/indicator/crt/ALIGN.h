

#pragma once
#ifndef INDICATOR_CRT_ALIGN_H_
#define INDICATOR_CRT_ALIGN_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 按指定日期对齐
 * @ingroup Indicator
 */
Indicator stradex_API ALIGN(const DatetimeList&);
Indicator ALIGN(const Indicator& ind, const DatetimeList& ref);
Indicator ALIGN(const Indicator& ind, const Indicator& ref);
Indicator ALIGN(const Indicator& ind, const KData& ref);

inline Indicator ALIGN(const Indicator& ind, const DatetimeList& ref) {
    return ALIGN(ref)(ind);
}

inline Indicator ALIGN(const Indicator& ind, const Indicator& ref) {
    return ALIGN(ref.getDatetimeList())(ind);
}

inline Indicator ALIGN(const Indicator& ind, const KData& ref) {
    return ALIGN(ref.getDatetimeList())(ind);
}

}  // namespace stradex

#endif
