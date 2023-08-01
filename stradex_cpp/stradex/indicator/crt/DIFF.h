/*
 * DIFF.h
 *
 *  Created on: 2013-4-18
 *      Author: jialuechen
 */

#pragma once
#ifndef DIFF_H_
#define DIFF_H_

#include "../Indicator.h"

namespace stradex {

/**
 * 差分指标，即data[i] - data[i-1]
 * @ingroup Indicator
 */
Indicator stradex_API DIFF();

/**
 * 差分指标，即data[i] - data[i-1]
 * @param data 待计算数据
 * @ingroup Indicator
 */
Indicator stradex_API DIFF(const Indicator& data);

}  // namespace stradex

#endif /* DIFF_H_ */
