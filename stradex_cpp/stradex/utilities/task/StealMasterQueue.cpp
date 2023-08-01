

#include "StealMasterQueue.h"

namespace stradex {


void StealMasterQueue::push(const StealTaskPtr& item) {
    std::lock_guard<std::mutex> lk(m_mutex);
    m_queue.push(item);
    m_cond.notify_one();
}


StealTaskPtr StealMasterQueue::wait_and_pop() {
    std::unique_lock<std::mutex> lk(m_mutex);
    m_cond.wait(lk, [this] { return !m_queue.empty(); });
    auto result = m_queue.front();
    m_queue.pop();
    return result;
}


StealTaskPtr StealMasterQueue::try_pop() {
    std::lock_guard<std::mutex> lk(m_mutex);
    StealTaskPtr result;
    if (m_queue.empty()) {
        return result;
    }
    result = m_queue.front();
    m_queue.pop();
    return result;
}


bool StealMasterQueue::empty() const {
    std::lock_guard<std::mutex> lk(m_mutex);
    return m_queue.empty();
}

}  