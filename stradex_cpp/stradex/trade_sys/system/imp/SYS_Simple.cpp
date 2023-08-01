/*
 * SYS_Simple.cpp
 *
 *  Created on: 2013-5-7
 *      Author: jialuechen
 */

#include "../crt/SYS_Simple.h"

namespace stradex {

SystemPtr stradex_API SYS_Simple(const TradeManagerPtr& tm, const MoneyManagerPtr& mm,
                             const EnvironmentPtr& ev, const ConditionPtr& cn, const SignalPtr& sg,
                             const StoplossPtr& sl, const StoplossPtr& tp, const ProfitGoalPtr& pg,
                             const SlippagePtr& sp) {
    return SystemPtr(new System(tm, mm, ev, cn, sg, sl, tp, pg, sp, "SYS_Simple"));
}

} /* namespace stradex */
