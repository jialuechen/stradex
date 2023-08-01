
#pragma once

#include "../../utilities/TimerManager.h"

namespace stradex {


TimerManager *getScheduler();


void releaseScheduler();

}  // namespace stradex