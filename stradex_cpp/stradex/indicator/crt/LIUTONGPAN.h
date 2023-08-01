/*
 * LIUTONGPANG.h
 *
 *  Created on: 2019年3月6日
 *      Author: jialuechen
 */

#pragma once
#ifndef INDICATOR_CRT_LIUTONGPAN_H_
#define INDICATOR_CRT_LIUTONGPAN_H_

#include "../Indicator.h"

#define CAPITAL LIUTONGPAN

namespace stradex {

Indicator stradex_API LIUTONGPAN();
Indicator stradex_API LIUTONGPAN(const KData&);

}  // namespace stradex

#endif /* INDICATOR_CRT_LIUTONGPAN_H_ */
