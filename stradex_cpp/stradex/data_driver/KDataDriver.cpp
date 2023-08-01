#include "../StockManager.h"
#include "KDataDriver.h"

namespace stradex {

stradex_API std::ostream& operator<<(std::ostream& os, const KDataDriver& driver) {
    os << "KDataDriver(" << driver.name() << ", " << driver.getParameter() << ")";
    return os;
}

stradex_API std::ostream& operator<<(std::ostream& os, const KDataDriverPtr& driver) {
    if (driver) {
        os << *driver;
    } else {
        os << "KDataDriver(NULL)";
    }

    return os;
}

KDataDriver::KDataDriver() : m_name("") {}

KDataDriver::KDataDriver(const Parameter& params) : m_params(params) {}

KDataDriver::KDataDriver(const string& name) : m_name(name) {
    to_upper(m_name);
}

shared_ptr<KDataDriver> KDataDriver::clone() {
    shared_ptr<KDataDriver> ptr = _clone();
    ptr->m_params = m_params;
    ptr->m_name = m_name;
    ptr->_init();
    return ptr;
}

bool KDataDriver::checkType() {
    bool result = false;
    try {
        string type = getParam<string>("type");
        to_upper(type);
        if (type == m_name) {
            result = true;
        } else {
            result = false;
            stradex_WARN("Type of driver mismatch! ({} != {})", type, m_name);
        }

    } catch (...) {
        result = false;
        stradex_ERROR("Can't get type of driver!");
    }

    return result;
}

bool KDataDriver::init(const Parameter& params) {
    stradex_IF_RETURN(m_params == params, true);
    m_params = params;
    stradex_IF_RETURN(!checkType(), false);
    return _init();
}

size_t KDataDriver::getCount(const string& market, const string& code, KQuery::KType kType) {
    stradex_INFO("The getCount method has not been implemented! (KDataDriver: {})", m_name);
    return 0;
}

bool KDataDriver::getIndexRangeByDate(const string& market, const string& code, const KQuery& query,
                                      size_t& out_start, size_t& out_end) {
    stradex_INFO("The getIndexRangeByDate method has not been implemented! (KDataDriver: {})", m_name);
    return false;
}

KRecordList KDataDriver::getKRecordList(const string& market, const string& code,
                                        const KQuery& query) {
    stradex_INFO("The getKRecordList method has not been implemented! (KDataDriver: {})", m_name);
    return KRecordList();
}

TimeLineList KDataDriver::getTimeLineList(const string& market, const string& code,
                                          const KQuery& query) {
    stradex_INFO("The getTimeLineList method has not been implemented! (KDataDriver: {})", m_name);
    return TimeLineList();
}

TransList KDataDriver::getTransList(const string& market, const string& code, const KQuery& query) {
    stradex_INFO("The getTransList method has not been implemented! (KDataDriver: {})", m_name);
    return TransList();
}

} /* namespace stradex */
