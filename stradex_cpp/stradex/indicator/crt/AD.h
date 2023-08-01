

#pragma once
#ifndef INDICATOR_CRT_AD_H_
#define INDICATOR_CRT_AD_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 累积/派发线
 * @param k 关联的 KData 数据
 * @ingroup Indicator
 */
Indicator stradex_API AD(const KData& k);
Indicator stradex_API AD();

}  // namespace stradex

#endif
