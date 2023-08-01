#pragma once

#include "../SelectorBase.h"

namespace stradex {

SEPtr stradex_API SE_Signal();

SEPtr stradex_API SE_Signal(const StockList& stock_list, const SystemPtr& sys);

}  // namespace stradex