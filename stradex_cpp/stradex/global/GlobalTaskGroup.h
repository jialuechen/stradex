#pragma once
#ifndef stradex_GLOBAL_TASK_GROUP
#define stradex_GLOBAL_TASK_GROUP

#include "../utilities/thread/StealThreadPool.h"

namespace stradex {

StealThreadPool* getGlobalTaskGroup();

template <typename ResultType>
using task_handle = std::future<ResultType>;

template <typename FunctionType>
task_handle<typename std::result_of<FunctionType()>::type> addTask(FunctionType f) {
    return getGlobalTaskGroup()->submit(f);
}

void releaseGlobalTaskGroup();

} /* namespace stradex */

#endif /* stradex_GLOBAL_TASK_GROUP */
