

#include "StealRunnerQueue.h"

namespace stradex {


void StealRunnerQueue::push_front(const StealTaskPtr& task) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push_front(task);
}


void StealRunnerQueue::push_back(const StealTaskPtr& task) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push_back(task);
}


bool StealRunnerQueue::empty() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.empty();
}


StealTaskPtr StealRunnerQueue::try_pop() {
    std::lock_guard<std::mutex> lock(m_mutex);
    StealTaskPtr result;
    if (m_queue.empty()) {
        return result;
    }

    result = m_queue.front();
    m_queue.pop_front();
    return result;
}


StealTaskPtr StealRunnerQueue::try_steal() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_queue.empty()) {
        return StealTaskPtr();
    }

    StealTaskPtr result = m_queue.back();
    if (typeid(*result) == typeid(StopTask)) {
        return StealTaskPtr();
    }

    m_queue.pop_back();
    return result;
}

}