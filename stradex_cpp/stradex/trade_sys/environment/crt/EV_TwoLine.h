#pragma once
#ifndef TRADE_SYS_ENVIRONMENT_CRT_EV_TWOLINE_H_
#define TRADE_SYS_ENVIRONMENT_CRT_EV_TWOLINE_H_

#include "../../../indicator/Indicator.h"
#include "../EnvironmentBase.h"

namespace stradex {

EVPtr stradex_API EV_TwoLine(const Indicator& fast, const Indicator& slow, const string& market);

} /* namespace stradex */

#endif /* TRADE_SYS_ENVIRONMENT_CRT_EV_TWOLINE_H_ */
