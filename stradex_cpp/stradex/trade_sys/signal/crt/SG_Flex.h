/*
 * FLEX._SG.h
 *
 *  Created on: 2015年3月21日
 *      Author: jialuechen
 */

#pragma once
#ifndef TRADE_SYS_SIGNAL_CRT_FLEX_SG_H_
#define TRADE_SYS_SIGNAL_CRT_FLEX_SG_H_

#include "../../../indicator/Indicator.h"
#include "../SignalBase.h"

namespace stradex {

/**
 * 自交叉单线拐点指示器。
 * 使用自身的EMA(slow_n)作为慢线，自身作为快线，快线向上穿越慢线买入，快线向下穿越慢线卖出。
 * @param op
 * @param slow_n 慢线EMA周期
 * @param kpart KDATA|OPEN|HIGH|LOW|CLOSE|AMO|VOL
 * @return 信号指示器
 * @ingroup Signal
 */
SignalPtr stradex_API SG_Flex(const Indicator& op, int slow_n, const string& kpart = "CLOSE");

} /* namespace stradex */

#endif /* TRADE_SYS_SIGNAL_CRT_FLEX_SG_H_ */
