/*
 * TradeRequest.cpp
 *
 *  Created on: 2013-4-20
 *      Author: jialuechen
 */

#include "TradeRequest.h"
#include "SystemPart.h"

namespace stradex {

TradeRequest::TradeRequest()
: valid(false),
  business(BUSINESS_INVALID),
  datetime(Null<Datetime>()),
  stoploss(0.0),
  goal(0.0),
  number(0),
  from(PART_INVALID),
  count(0) {}

void TradeRequest::clear() {
    valid = false;
    business = BUSINESS_INVALID;
    datetime = Null<Datetime>();
    stoploss = 0.0;
    goal = 0.0;
    number = 0;
    from = PART_INVALID;
    count = 0;
}

} /* namespace stradex */
