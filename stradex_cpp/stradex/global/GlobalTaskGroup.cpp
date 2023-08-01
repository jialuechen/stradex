#include "GlobalTaskGroup.h"
#include "../Log.h"

namespace stradex {

static StealThreadPool* g_threadPool;

StealThreadPool* getGlobalTaskGroup() {
    static std::once_flag oc;
    std::call_once(oc, [&]() {
        auto cpu_num = std::thread::hardware_concurrency();
        if (cpu_num >= 4) {
            cpu_num -= 2;
        } else if (cpu_num > 1) {
            cpu_num--;
        }
        g_threadPool = new StealThreadPool(cpu_num);
    });
    return g_threadPool;
}

void releaseGlobalTaskGroup() {
    stradex_TRACE("releaseGlobalTaskGroup");
    if (g_threadPool) {
        g_threadPool->stop();
        delete g_threadPool;
        g_threadPool = nullptr;
    }
}

} /* namespace stradex */