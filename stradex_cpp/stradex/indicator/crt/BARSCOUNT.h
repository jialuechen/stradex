

#pragma once
#ifndef INDICATOR_CRT_BARSCOUNT_H_
#define INDICATOR_CRT_BARSCOUNT_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 有效值周期数, 求总的周期数。
 * @details
 * <pre>
 * 用法：BARSCOUNT(X)第一个有效数据到当前的天数。
 * 例如：BARSCOUNT(CLOSE)对于日线数据取得上市以来总交易日数，
 *       对于1分钟线取得当日交易分钟数
 * </pre>
 * @ingroup Indicator
 */
Indicator stradex_API BARSCOUNT();
Indicator BARSCOUNT(const Indicator& ind);

inline Indicator BARSCOUNT(const Indicator& ind) {
    return BARSCOUNT()(ind);
}

}  // namespace stradex

#endif
