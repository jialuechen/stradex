/*
 * TC_Zero.h
 *
 *  Created on: 2013-2-14
 *      Author: jialuechen
 */

#pragma once
#ifndef CRTZEROTC_H_
#define CRTZEROTC_H_

#include "../TradeCostBase.h"

namespace stradex {

/**
 * 创建零成本算法实例
 * @see ZeroTradeCost
 * @ingroup TradeCost
 */
TradeCostPtr stradex_API TC_Zero();

}  // namespace stradex

#endif /* CRTZEROTC_H_ */
