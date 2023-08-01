

#include "Indicator.h"
#include "IndParam.h"

namespace stradex {

stradex_API std::ostream& operator<<(std::ostream& os, const IndParam& ind) {
    os << "IndParam: \n" << ind.m_ind->formula();
    return os;
}

IndParam::IndParam() {}

IndParam::IndParam(const IndicatorImpPtr& ind) : m_ind(ind){};

IndParam::IndParam(const Indicator& ind) : m_ind(ind.getImp()){};

Indicator IndParam::get() const {
    return Indicator(m_ind);
}

}