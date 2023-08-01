#include "EnvironmentBase.h"

namespace stradex {

stradex_API std::ostream& operator<<(std::ostream& os, const EnvironmentBase& en) {
    os << "Environment(" << en.name() << " " << en.getParameter() << ")";
    return os;
}

stradex_API std::ostream& operator<<(std::ostream& os, const EnvironmentPtr& en) {
    if (en) {
        os << *en;
    } else {
        os << "Environment(NULL)";
    }
    return os;
}

EnvironmentBase::EnvironmentBase() : m_name("EnvironmentBase") {}

EnvironmentBase::EnvironmentBase(const string& name) : m_name(name) {}

EnvironmentBase::~EnvironmentBase() {}

void EnvironmentBase::reset() {
    m_query = Null<KQuery>();
    m_valid.clear();
    _reset();
}

EnvironmentPtr EnvironmentBase::clone() {
    EnvironmentPtr p;
    try {
        p = _clone();
    } catch (...) {
        stradex_ERROR("Subclass _clone failed!");
        p = EnvironmentPtr();
    }

    if (!p || p.get() == this) {
        stradex_ERROR("Failed clone! Will use self-ptr!");
        return shared_from_this();
    }

    p->m_params = m_params;
    p->m_name = m_name;
    p->m_query = m_query;
    p->m_valid = m_valid;
    return p;
}

void EnvironmentBase::setQuery(const KQuery& query) {
    if (m_query != query) {
        m_valid.clear();
        _reset();
        m_query = query;
        _calculate();
    }
}

void EnvironmentBase::_addValid(const Datetime& datetime) {
    m_valid.insert(datetime);
}

bool EnvironmentBase::isValid(const Datetime& datetime) {
    return m_valid.count(datetime) != 0;
}

} /* namespace stradex */
