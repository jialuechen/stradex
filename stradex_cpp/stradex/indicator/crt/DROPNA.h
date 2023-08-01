

#pragma once
#ifndef INDICATOR_CRT_DROPNA_H_
#define INDICATOR_CRT_DROPNA_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 删除nan值
 * @ingroup Indicator
 */
Indicator stradex_API DROPNA();
Indicator DROPNA(const Indicator& ind);

inline Indicator DROPNA(const Indicator& ind) {
    return DROPNA()(ind);
}

}  // namespace stradex

#endif
