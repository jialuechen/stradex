/*
 * PG_FixedPercent.h
 *
 *  Created on: 2016年5月6日
 *      Author: Administrator
 */

#pragma once
#ifndef TRADE_SYS_PROFITGOAL_CRT_PG_FIXEDHOLDDAYS_H_
#define TRADE_SYS_PROFITGOAL_CRT_PG_FIXEDHOLDDAYS_H_

#include "../ProfitGoalBase.h"

namespace stradex {

/**
 * 固定持仓天数盈利目标策略
 * @param days: 允许持仓天数（按交易日算）,默认5天
 * @return PGPtr
 * @ingroup ProfitGoal
 */
ProfitGoalPtr stradex_API PG_FixedHoldDays(int days = 5);

} /* namespace stradex */

#endif /* TRADE_SYS_PROFITGOAL_CRT_PG_FIXEDPERCENT_H_ */
