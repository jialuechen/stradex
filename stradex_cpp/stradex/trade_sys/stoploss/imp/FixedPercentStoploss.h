#pragma once
#ifndef FIXEDPERCENTSTOPLOSS_H_
#define FIXEDPERCENTSTOPLOSS_H_

#include "../StoplossBase.h"

namespace stradex {

class FixedPercentStoploss : public StoplossBase {
    STOPLOSS_IMP(FixedPercentStoploss, "FixedPercentSL")
    STOPLOSS_NO_PRIVATE_MEMBER_SERIALIZATION

public:
    FixedPercentStoploss();
    virtual ~FixedPercentStoploss();
};

} /* namespace stradex */
#endif /* FIXEDPERCENTSTOPLOSS_H_ */
