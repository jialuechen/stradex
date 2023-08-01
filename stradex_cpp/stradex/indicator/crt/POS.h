/*
 * POS.h
 *
 *  Created on: 2015年3月17日
 *      Author: jialuechen
 */

#pragma once
#ifndef INDICATOR_CRT_POS_H_
#define INDICATOR_CRT_POS_H_

#include "../../trade_sys/signal/SignalBase.h"
#include "../../Block.h"

namespace stradex {

Indicator stradex_API POS(const Block& block, KQuery query, SignalPtr ind);

} /* namespace stradex */

#endif /* INDICATOR_CRT_POS_H_ */
