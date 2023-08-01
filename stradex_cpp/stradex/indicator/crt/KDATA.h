/*
 * IKDATA.h
 *
 *  Created on: 2013-2-14
 *      Author: jialuechen
 */

#pragma once
#include "../Indicator.h"

namespace stradex {

/**
 * 包装KData成Indicator，用于其他指标计算
 * @ingroup Indicator
 */
Indicator stradex_API KDATA();
Indicator stradex_API KDATA(const KData&);

/**
 * 包装KData的开盘价成Indicator，用于其他指标计算
 * @ingroup Indicator
 */
Indicator stradex_API OPEN();
Indicator stradex_API OPEN(const KData&);

/**
 * 包装KData的最高价成Indicator，用于其他指标计算
 * @ingroup Indicator
 */
Indicator stradex_API HIGH();
Indicator stradex_API HIGH(const KData&);

/**
 * 包装KData的最低价成Indicator，用于其他指标计算
 * @ingroup Indicator
 */
Indicator stradex_API LOW();
Indicator stradex_API LOW(const KData&);

/**
 * 包装KData的收盘价成Indicator，用于其他指标计算
 * @ingroup Indicator
 */
Indicator stradex_API CLOSE();
Indicator stradex_API CLOSE(const KData&);

/**
 * 包装KData的成交金额成Indicator，用于其他指标计算
 * @ingroup Indicator
 */
Indicator stradex_API AMO();
Indicator stradex_API AMO(const KData&);

/**
 * 包装KData的成交量成Indicator，用于其他指标计算
 * @ingroup Indicator
 */
Indicator stradex_API VOL();
Indicator stradex_API VOL(const KData&);

/**
 * 根据字符串选择返回KDATA/OPEN/HIGH/LOW/CLOSE/AMO/VOL
 * @param kdata K线数据
 * @param kpart KDATA|OPEN|HIGH|LOW|CLOSE|AMO|VOL
 * @see KDATA, OPEN, HIGH, LOW, CLOSE, AMO, VOL
 * @ingroup Indicator
 */
Indicator stradex_API KDATA_PART(const KData& kdata, const string& kpart);
Indicator stradex_API KDATA_PART(const string& kpart);

}  // namespace stradex
