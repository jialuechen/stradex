/*
 * CROSS_SG.h
 *
 *  Created on: 2015年2月20日
 *      Author: jialuechen
 */

#pragma once
#ifndef TRADE_SYS_SIGNAL_CRT_SG_CROSSGOLD_H_
#define TRADE_SYS_SIGNAL_CRT_SG_CROSSGOLD_H_

#include "../../../indicator/Indicator.h"
#include "../SignalBase.h"

namespace stradex {

/**
 * 金叉指示器，当快线从下向上穿越慢线且快线和慢线的方向都是向上时为金叉，买入；
 * 当快线从上向下穿越慢线且快线和慢线的方向都是向下时死叉，卖出。
 * @param fast 快线
 * @param slow 慢线
 * @param kpart KDATA|OPEN|HIGH|LOW|CLOSE|AMO|VOL
 * @return 信号指示器
 * @ingroup Signal
 */
SignalPtr stradex_API SG_CrossGold(const Indicator& fast, const Indicator& slow,
                               const string& kpart = "CLOSE");

} /* namespace stradex */

#endif /* TRADE_SYS_SIGNAL_CRT_SG_CROSSGOLD_H_ */
