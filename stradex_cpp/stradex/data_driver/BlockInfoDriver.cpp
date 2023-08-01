#include "BlockInfoDriver.h"

namespace stradex {

stradex_API std::ostream& operator<<(std::ostream& os, const BlockInfoDriver& driver) {
    os << "BlockInfoDriver(" << driver.name() << ", " << driver.getParameter() << ")";
    return os;
}

stradex_API std::ostream& operator<<(std::ostream& os, const BlockInfoDriverPtr& driver) {
    if (driver) {
        os << *driver;
    } else {
        os << "BlockInfoDriver(NULL)";
    }

    return os;
}

BlockInfoDriver::BlockInfoDriver(const string& name) : m_name(name) {
    to_upper(m_name);
}

bool BlockInfoDriver::checkType() {
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

bool BlockInfoDriver::init(const Parameter& params) {
    stradex_IF_RETURN(m_params == params, true);
    m_params = params;
    stradex_IF_RETURN(!checkType(), false);
    return _init();
}

} /* namespace stradex */
