/*
 * SG_Flex.cpp
 *
 *  Created on: 2016年4月11日
 *      Author: jialuechen
 */

#include "../../../indicator/crt/EMA.h"
#include "SG_Cross.h"

namespace stradex {

SignalPtr stradex_API SG_Flex(const Indicator& op, int slow_n, const string& kpart) {
    SignalPtr sg = SG_Cross(op, EMA(slow_n)(op), kpart);
    sg->name("SG_Flex");
    return sg;
}

} /* namespace stradex */
