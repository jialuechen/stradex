#include "Indicator.h"
#include "crt/CVAL.h"

namespace stradex {

stradex_API std::ostream& operator<<(std::ostream& os, const Indicator& indicator) {
    os << indicator.m_imp;
    return os;
}

Indicator::Indicator(const IndicatorImpPtr& imp) : m_imp(imp) {}

Indicator::Indicator(const Indicator& indicator) : m_imp(indicator.m_imp) {}

Indicator::Indicator(Indicator&& ind) : m_imp(std::move(ind.m_imp)) {}

Indicator::~Indicator() {}

string Indicator::formula() const {
    return m_imp ? m_imp->formula() : "Indicator";
}

Indicator Indicator::operator()(const KData& k) {
    Indicator result = clone();
    result.setContext(k);
    return result;
}

void Indicator::setContext(const Stock& stock, const KQuery& query) {
    if (m_imp)
        m_imp->setContext(stock, query);
}

void Indicator::setContext(const KData& k) {
    if (m_imp)
        m_imp->setContext(k);
}

KData Indicator::getContext() const {
    return m_imp ? m_imp->getContext() : KData();
}

Indicator& Indicator::operator=(const Indicator& indicator) {
    stradex_IF_RETURN(this == &indicator, *this);
    m_imp = indicator.m_imp;
    return *this;
}

Indicator& Indicator::operator=(Indicator&& indicator) {
    stradex_IF_RETURN(this == &indicator, *this);
    m_imp = std::move(indicator.m_imp);
    return *this;
}

PriceList Indicator::getResultAsPriceList(size_t num) const {
    stradex_WARN_IF_RETURN(!m_imp, PriceList(), "indicator imptr is null!");
    return m_imp->getResultAsPriceList(num);
}

Indicator Indicator::getResult(size_t num) const {
    stradex_WARN_IF_RETURN(!m_imp, Indicator(), "indicator imptr is null!");
    return m_imp->getResult(num);
}

Indicator Indicator::operator()(const Indicator& ind) {
    stradex_IF_RETURN(!m_imp, Indicator());
    stradex_IF_RETURN(!ind.getImp(), Indicator(m_imp));
    IndicatorImpPtr p = m_imp->clone();
    p->add(IndicatorImp::OP, IndicatorImpPtr(), ind.getImp());
    return p->calculate();
}

stradex_API Indicator operator+(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::ADD, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator-(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::SUB, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator*(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::MUL, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator/(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::DIV, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator%(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::MOD, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator==(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::EQ, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator!=(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::NE, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator>(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::GT, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator<(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::LT, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator>=(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::GE, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator<=(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::LE, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator&(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::AND, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator|(const Indicator& ind1, const Indicator& ind2) {
    stradex_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator());
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::OR, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

stradex_API Indicator operator+(const Indicator& ind, price_t val) {
    return ind + CVAL(ind, val);
}

stradex_API Indicator operator+(price_t val, const Indicator& ind) {
    return CVAL(ind, val) + ind;
}

stradex_API Indicator operator-(const Indicator& ind, price_t val) {
    return ind - CVAL(ind, val);
}

stradex_API Indicator operator-(price_t val, const Indicator& ind) {
    return CVAL(ind, val) - ind;
}

stradex_API Indicator operator*(const Indicator& ind, price_t val) {
    return ind * CVAL(ind, val);
}

stradex_API Indicator operator*(price_t val, const Indicator& ind) {
    return CVAL(ind, val) * ind;
}

stradex_API Indicator operator/(const Indicator& ind, price_t val) {
    return ind / CVAL(ind, val);
}

stradex_API Indicator operator/(price_t val, const Indicator& ind) {
    return CVAL(ind, val) / ind;
}

stradex_API Indicator operator%(const Indicator& ind, price_t val) {
    return ind % CVAL(ind, val);
}

stradex_API Indicator operator%(price_t val, const Indicator& ind) {
    return CVAL(ind, val) % ind;
}

stradex_API Indicator operator==(const Indicator& ind, price_t val) {
    return ind == CVAL(ind, val);
}

stradex_API Indicator operator==(price_t val, const Indicator& ind) {
    return CVAL(ind, val) == ind;
}

stradex_API Indicator operator!=(const Indicator& ind, price_t val) {
    return ind != CVAL(ind, val);
}

stradex_API Indicator operator!=(price_t val, const Indicator& ind) {
    return CVAL(ind, val) != ind;
}

stradex_API Indicator operator>(const Indicator& ind, price_t val) {
    return ind > CVAL(ind, val);
}

stradex_API Indicator operator>(price_t val, const Indicator& ind) {
    return CVAL(ind, val) > ind;
}

stradex_API Indicator operator<(const Indicator& ind, price_t val) {
    return ind < CVAL(ind, val);
}

stradex_API Indicator operator<(price_t val, const Indicator& ind) {
    return CVAL(ind, val) < ind;
}

stradex_API Indicator operator>=(const Indicator& ind, price_t val) {
    return ind >= CVAL(ind, val);
}

stradex_API Indicator operator>=(price_t val, const Indicator& ind) {
    return CVAL(ind, val) >= ind;
}

stradex_API Indicator operator<=(const Indicator& ind, price_t val) {
    return ind <= CVAL(ind, val);
}

stradex_API Indicator operator<=(price_t val, const Indicator& ind) {
    return CVAL(ind, val) <= ind;
}

stradex_API Indicator operator&(const Indicator& ind, price_t val) {
    return ind & CVAL(ind, val);
}

stradex_API Indicator operator&(price_t val, const Indicator& ind) {
    return CVAL(ind, val) & ind;
}

stradex_API Indicator operator|(const Indicator& ind, price_t val) {
    return ind | CVAL(ind, val);
}

stradex_API Indicator operator|(price_t val, const Indicator& ind) {
    return CVAL(ind, val) | ind;
}

Indicator stradex_API WEAVE(const Indicator& ind1, const Indicator& ind2) {
    stradex_ERROR_IF_RETURN(!ind1.getImp() || !ind2.getImp(), Indicator(),
                        "ind1 or ind2 is Null Indicator!");
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add(IndicatorImp::WEAVE, ind1.getImp(), ind2.getImp());
    return p->calculate();
}

Indicator stradex_API IF(const Indicator& ind1, const Indicator& ind2, const Indicator& ind3) {
    stradex_ERROR_IF_RETURN(!ind1.getImp() || !ind2.getImp() || !ind3.getImp(), Indicator(),
                        "Exists null indicator!");
    IndicatorImpPtr p = make_shared<IndicatorImp>();
    p->add_if(ind1.getImp(), ind2.getImp(), ind3.getImp());
    return p->calculate();
}

Indicator stradex_API IF(const Indicator& x, price_t a, const Indicator& b) {
    return IF(x, CVAL(b, a), b);
}

Indicator stradex_API IF(const Indicator& x, const Indicator& a, price_t b) {
    return IF(x, a, CVAL(a, b));
}

Indicator stradex_API IF(const Indicator& x, price_t a, price_t b) {
    return IF(x, CVAL(x, a), CVAL(x, b));
}

} /* namespace stradex */
