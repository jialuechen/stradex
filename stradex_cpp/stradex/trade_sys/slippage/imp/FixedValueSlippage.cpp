/*
 * FixedValueSlippage.cpp
 *
 *  Created on: 2016年5月7日
 *      Author: Administrator
 */

#include "FixedValueSlippage.h"

namespace stradex {

FixedValueSlippage::FixedValueSlippage() {
    setParam<double>("value", 0.01);
}

FixedValueSlippage::~FixedValueSlippage() {}

price_t FixedValueSlippage ::getRealBuyPrice(const Datetime& datetime, price_t price) {
    return price + getParam<double>("value");
}

price_t FixedValueSlippage ::getRealSellPrice(const Datetime& datetime, price_t price) {
    return price - getParam<double>("value");
}

void FixedValueSlippage::_calculate() {}

SlippagePtr stradex_API SP_FixedValue(double value) {
    FixedValueSlippage* ptr = new FixedValueSlippage;
    ptr->setParam("value", value);
    return SlippagePtr(ptr);
}

} /* namespace stradex */
