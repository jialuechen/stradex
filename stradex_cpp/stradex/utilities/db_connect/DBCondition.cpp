

#include "DBCondition.h"

namespace stradex {

DBCondition& DBCondition::operator&(const DBCondition& other) {
    if (this == &other) {
        return *this;
    }

    if (m_condition.empty()) {
        m_condition = other.m_condition;
    } else {
        m_condition = fmt::format("({} and {})", m_condition, other.m_condition);
    }

    return *this;
}

DBCondition& DBCondition::operator|(const DBCondition& other) {
    if (this == &other) {
        return *this;
    }

    if (m_condition.empty()) {
        m_condition = other.m_condition;
    } else {
        m_condition = fmt::format("({} or {})", m_condition, other.m_condition);
    }

    return *this;
}

}  // namespace stradex