#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <memory>
#include "../utilities/Parameter.h"

namespace STRADEX {


template <class DriverConnectT>
class DriverConnectPool {
public:
    DriverConnectPool() = delete;
    DriverConnectPool(const DriverConnectPool &) = delete;
    DriverConnectPool &operator=(const DriverConnectPool &) = delete;

    typedef typename DriverConnectT::DriverTypePtr DriverPtr;
    typedef std::shared_ptr<DriverConnectT> DriverConnectPtr;

    explicit DriverConnectPool(const DriverPtr &prototype, size_t maxConnect = 0,
                               size_t maxIdleConnect = std::thread::hardware_concurrency())
    : m_maxSize(maxConnect),
      m_maxIdelSize(maxIdleConnect),
      m_count(0),
      m_prototype(prototype),
      m_closer(this) {}

    
    virtual ~DriverConnectPool() {
        while (!m_driverList.empty()) {
            DriverConnectT *p = m_driverList.front();
            m_driverList.pop();
            if (p) {
                delete p;
            }
        }
    }

    DriverConnectPtr getConnect() noexcept {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_driverList.empty()) {
            if (m_maxSize > 0 && m_count >= m_maxSize) {
                m_cond.wait(lock, [this] { return !m_driverList.empty(); });
            } else {
                m_count++;
                return DriverConnectPtr(new DriverConnectT(m_prototype->clone()), m_closer);
            }
        }
        DriverConnectT *p = m_driverList.front();
        m_driverList.pop();
        return DriverConnectPtr(p, m_closer);
    }

    DriverPtr getPrototype() {
        return m_prototype;
    }

    
    size_t count() const {
        return m_count;
    }

    
    size_t idleCount() const {
        return m_driverList.size();
    }

    void releaseIdleConnect() {
        std::lock_guard<std::mutex> lock(m_mutex);
        while (!m_driverList.empty()) {
            DriverConnectT *p = m_driverList.front();
            m_driverList.pop();
            m_count--;
            if (p) {
                delete p;
            }
        }
    }

private:
    void returnDriver(DriverConnectT *p) {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (p) {
            if (m_driverList.size() < m_maxIdelSize) {
                m_driverList.push(p);
                m_cond.notify_all();
            } else {
                delete p;
                m_count--;
            }
        } else {
            m_count--;
            STRADEX_WARN("Trying to return an empty pointer!");
        }
    }

private:
    size_t m_maxSize;       
    size_t m_maxIdelSize;   
    size_t m_count;         
    DriverPtr m_prototype;  
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::queue<DriverConnectT *> m_driverList;

    class DriverCloser {
    public:
        explicit DriverCloser(DriverConnectPool *pool) : m_pool(pool) {}
        void operator()(DriverConnectT *conn) {
            if (m_pool && conn) {
                m_pool->returnDriver(conn);
            }
        }

    private:
        DriverConnectPool *m_pool;
    };

    DriverCloser m_closer;
};

}  
