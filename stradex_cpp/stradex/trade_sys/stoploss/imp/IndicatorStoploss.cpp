#include "../../../indicator/crt/KDATA.h"
#include "IndicatorStoploss.h"

namespace stradex {

IndicatorStoploss::IndicatorStoploss() : StoplossBase("IndicatorStoploss") {
    setParam<string>("kpart", "CLOSE");
}

IndicatorStoploss::IndicatorStoploss(const Indicator& op, const string& kdata_part)
: StoplossBase("IndicatorStoploss"), m_op(op) {
    setParam<string>("kpart", "CLOSE");
}

IndicatorStoploss::~IndicatorStoploss() {}

price_t IndicatorStoploss::getPrice(const Datetime& datetime, price_t price) {
    return m_result.count(datetime) ? m_result[datetime] : 0.0;
}

void IndicatorStoploss::_reset() {
    m_result.clear();
}

StoplossPtr IndicatorStoploss::_clone() {
    IndicatorStoploss* p = new IndicatorStoploss(m_op, getParam<string>("kpart"));
    p->m_result = m_result;
    return StoplossPtr(p);
}

void IndicatorStoploss::_calculate() {
    Indicator ind = m_op(KDATA_PART(m_kdata, getParam<string>("kpart")));
    size_t total = ind.size();
    for (size_t i = ind.discard(); i < total; ++i) {
        m_result[m_kdata[i].datetime] = ind[i];
    }
}

StoplossPtr stradex_API ST_Indicator(const Indicator& op, const string& kpart) {
    return StoplossPtr(new IndicatorStoploss(op, kpart));
}

} /* namespace stradex */
