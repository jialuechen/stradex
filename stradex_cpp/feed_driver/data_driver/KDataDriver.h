#pragma once
#ifndef KDATADRIVER_H_
#define KDATADRIVER_H_

#include "../utilities/Parameter.h"
#include "../KQuery.h"
#include "../TimeLineRecord.h"
#include "../TransRecord.h"

namespace STRADEX {

class STRADEX_API KDataDriver {
    PARAMETER_SUPPORT

public:
    KDataDriver();

    KDataDriver(const Parameter& params);

    /**
     * 
     * @param name 
     */
    KDataDriver(const string& name);
    virtual ~KDataDriver() {}

    const string& name() const;


    bool init(const Parameter&);

    typedef shared_ptr<KDataDriver> KDataDriverPtr;
   
    KDataDriverPtr clone();

    
    virtual KDataDriverPtr _clone() = 0;

    
    virtual bool _init() {
        return true;
    }

    
    virtual bool isIndexFirst() = 0;

    
    virtual bool canParallelLoad() = 0;

    
    virtual size_t getCount(const string& market, const string& code, KQuery::KType kType);

    virtual bool getIndexRangeByDate(const string& market, const string& code, const KQuery& query,
                                     size_t& out_start, size_t& out_end);

    
    virtual KRecordList getKRecordList(const string& market, const string& code,
                                       const KQuery& query);

    
    virtual TimeLineList getTimeLineList(const string& market, const string& code,
                                         const KQuery& query);

    
    virtual TransList getTransList(const string& market, const string& code, const KQuery& query);

private:
    bool checkType();

private:
    string m_name;
};

typedef shared_ptr<KDataDriver> KDataDriverPtr;

STRADEX_API std::ostream& operator<<(std::ostream&, const KDataDriver&);
STRADEX_API std::ostream& operator<<(std::ostream&, const KDataDriverPtr&);

inline const string& KDataDriver::name() const {
    return m_name;
}

class KDataDriverConnect {
public:
    typedef KDataDriver DriverType;
    typedef KDataDriverPtr DriverTypePtr;

    explicit KDataDriverConnect(const KDataDriverPtr& driver) : m_driver(driver) {}
    ~KDataDriverConnect() = default;

    KDataDriverConnect(const KDataDriverConnect&) = delete;
    KDataDriverConnect(KDataDriverConnect&&) = delete;
    KDataDriverConnect& operator=(const KDataDriverConnect&) = delete;
    KDataDriverConnect& operator=(KDataDriverConnect&&) = delete;

    explicit operator bool() const noexcept {
        return m_driver.get() != nullptr;
    }

    const string& name() const {
        return m_driver->name();
    }

    bool isIndexFirst() {
        return m_driver->isIndexFirst();
    }

    bool canParallelLoad() {
        return m_driver->canParallelLoad();
    }

    size_t getCount(const string& market, const string& code, KQuery::KType kType) {
        return m_driver->getCount(market, code, kType);
    }

    bool getIndexRangeByDate(const string& market, const string& code, const KQuery& query,
                             size_t& out_start, size_t& out_end) {
        return m_driver->getIndexRangeByDate(market, code, query, out_start, out_end);
    }

    KRecordList getKRecordList(const string& market, const string& code, const KQuery& query) {
        return m_driver->getKRecordList(market, code, query);
    }

    TimeLineList getTimeLineList(const string& market, const string& code, const KQuery& query) {
        return m_driver->getTimeLineList(market, code, query);
    }

    TransList getTransList(const string& market, const string& code, const KQuery& query) {
        return m_driver->getTransList(market, code, query);
    }

private:
    KDataDriverPtr m_driver;
};

} 

#endif /* KDATADRIVER_H_ */
