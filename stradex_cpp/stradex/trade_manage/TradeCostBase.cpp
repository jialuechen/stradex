/*
 * TradeCostBase.cpp
 *
 *  Created on: 2013-2-13
 *      Author: jialuechen
 */

#include "TradeCostBase.h"

namespace stradex {

stradex_API std::ostream& operator<<(std::ostream& os, const TradeCostBase& tc) {
    os << "TradeCostFunc(" << tc.name() << ", " << tc.getParameter() << ")";
    return os;
}

stradex_API std::ostream& operator<<(std::ostream& os, const TradeCostPtr& tc) {
    if (tc) {
        os << *tc;
    } else {
        os << "TradeCostFunc(NULL)";
    }
    return os;
}

TradeCostBase::TradeCostBase(const string& name) : m_name(name) {}

TradeCostBase::~TradeCostBase() {}

TradeCostPtr TradeCostBase::clone() {
    TradeCostPtr result = _clone();
    TradeCostBase* p = result.get();
    p->m_params = m_params;
    p->m_name = m_name;
    return result;
}

} /* namespace stradex */
