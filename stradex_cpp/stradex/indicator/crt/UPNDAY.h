

#pragma once
#ifndef INDICATOR_CRT_UPNDAY_H_
#define INDICATOR_CRT_UPNDAY_H_

#include "EVERY.h"
#include "REF.h"

namespace stradex {

/**
 * 连涨周期, UPNDAY(CLOSE,M)表示连涨M个周期
 * @ingroup Indicator
 */
inline Indicator UPNDAY(const Indicator& ind, int n = 3) {
    Indicator result = EVERY(ind > REF(ind, 1), n);
    result.name("UPDAY");
    return result;
}

inline Indicator UPNDAY(const Indicator& ind, const IndParam& n) {
    Indicator result = EVERY(ind > REF(ind, 1), n);
    result.name("UPDAY");
    return result;
}

inline Indicator UPNDAY(const Indicator& ind, const Indicator& n) {
    Indicator result = EVERY(ind > REF(ind, 1), n);
    result.name("UPDAY");
    return result;
}

}  // namespace stradex

#endif
