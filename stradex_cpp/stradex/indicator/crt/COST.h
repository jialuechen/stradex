#pragma once
#ifndef INDICATOR_CRT_COST_H_
#define INDICATOR_CRT_COST_H_

#include "KDATA.h"

namespace stradex {

Indicator stradex_API COST(const KData& k, double x = 10.0);
Indicator stradex_API COST(double x = 10.0);

}  
#endif