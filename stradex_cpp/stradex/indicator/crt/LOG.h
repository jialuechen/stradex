/*
 * LOG.h
 *
 *  Created on: 2019-4-11
 *      Author: jialuechen
 */

#pragma once
#ifndef INDICATOR_CRT_LOG_H_
#define INDICATOR_CRT_LOG_H_

#include "CVAL.h"

namespace stradex {

/**
 * 以10为底的对数
 * 用法：LOG(X)取得X的对数
 * @ingroup Indicator
 */
Indicator stradex_API LOG();
Indicator LOG(price_t);
Indicator LOG(const Indicator& ind);

inline Indicator LOG(const Indicator& ind) {
    return LOG()(ind);
}

inline Indicator LOG(price_t val) {
    return LOG(CVAL(val));
}

}  // namespace stradex

#endif /* INDICATOR_CRT_LOG_H_ */
