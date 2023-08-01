/*
 * PG_FixedPercent.h
 *
 *  Created on: 2016年5月6日
 *      Author: Administrator
 */

#pragma once
#ifndef TRADE_SYS_PROFITGOAL_CRT_PG_FIXEDPERCENT_H_
#define TRADE_SYS_PROFITGOAL_CRT_PG_FIXEDPERCENT_H_

#include "../ProfitGoalBase.h"

namespace stradex {

/**
 * 固定百分比盈利目标，目标价格 = 买入价格 * (1 + p)
 * @param p 百分比
 * @return PGPtr
 */
ProfitGoalPtr stradex_API PG_FixedPercent(double p = 0.2);

} /* namespace stradex */

#endif /* TRADE_SYS_PROFITGOAL_CRT_PG_FIXEDPERCENT_H_ */
