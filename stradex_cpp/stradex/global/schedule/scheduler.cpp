#include <mutex>
#include "scheduler.h"
#include "../../Log.h"

namespace stradex {

static TimerManager *g_scheduler;

TimerManager *getScheduler() {
    static std::once_flag oc;
    std::call_once(oc, [&]() { g_scheduler = new TimerManager(2); });
    return g_scheduler;
}

void releaseScheduler() {
    stradex_TRACE("releaseScheduler");
    if (g_scheduler) {
        delete g_scheduler;
        g_scheduler = nullptr;
    }
}

}  // namespace stradex