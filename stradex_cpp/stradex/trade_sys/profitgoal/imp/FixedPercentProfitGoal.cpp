/*
 * FixedPercentProfitGoal.cpp
 *
 *  Created on: 2016年5月6日
 *      Author: Administrator
 */

#include "FixedPercentProfitGoal.h"

namespace stradex {

FixedPercentProfitGoal::FixedPercentProfitGoal() : ProfitGoalBase("PG_FixedPercent") {
    setParam<double>("p", 0.2);
}

FixedPercentProfitGoal::~FixedPercentProfitGoal() {}

void FixedPercentProfitGoal::_calculate() {}

price_t FixedPercentProfitGoal::getGoal(const Datetime& datetime, price_t price) {
    Stock stock = getTO().getStock();
    PositionRecord position = getTM()->getPosition(datetime, stock);
    return position.number != 0
             ? (position.buyMoney / position.number) * (1 + getParam<double>("p"))
             : price * (1 + getParam<double>("p"));
}

ProfitGoalPtr stradex_API PG_FixedPercent(double p) {
    ProfitGoalPtr ptr = make_shared<FixedPercentProfitGoal>();
    ptr->setParam<double>("p", p);
    return ptr;
}

} /* namespace stradex */
