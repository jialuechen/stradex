/*
 * crtTM.cpp
 *
 *  Created on: 2013-2-13
 *      Author: jialuechen
 */

#include "crtTM.h"

namespace stradex {

TradeManagerPtr stradex_API crtTM(const Datetime& datetime, price_t initcash,
                              const TradeCostPtr& costfunc, const string& name) {
    return TradeManagerPtr(new TradeManager(datetime, initcash, costfunc, name));
}

}  // namespace stradex
