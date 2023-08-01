/*
 * TC_TestStub.cpp
 *
 *  Created on: 2013-5-9
 *      Author: jialuechen
 */

#include "../imp/TradeCostStub.h"

namespace stradex {

stradex_API TradeCostPtr TC_TestStub() {
    return TradeCostPtr(new TradeCostStub());
}

}  // namespace stradex
