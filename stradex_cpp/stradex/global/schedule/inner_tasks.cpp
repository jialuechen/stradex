#include "inner_tasks.h"
#include "scheduler.h"
#include "../GlobalTaskGroup.h"
#include "../../StockManager.h"

namespace stradex {

void initInnerTasek() {
    auto* tm = getScheduler();
    tm->addFuncAtTimeEveryDay(Datetime::min(), Datetime::max(), TimeDelta(), reloadstradexTask);
    tm->start();
}

void reloadstradexTask() {
    StockManager::instance().reload();
}

} 