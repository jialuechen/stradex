

#pragma once
#ifndef INDICATOR_CRT_TIMELINEVOL_H_
#define INDICATOR_CRT_TIMELINEVOL_H_

#include "../Indicator.h"

namespace stradex {

Indicator stradex_API TIMELINEVOL();
Indicator stradex_API TIMELINEVOL(const KData&);

}  // namespace stradex

#endif
