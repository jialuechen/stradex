#include "../allocatefunds/SystemWeight.h"

namespace stradex {

stradex_API std::ostream& operator<<(std::ostream& os, const SystemWeight& sw) {
    os << std::fixed;
    os.precision(4);

    string name("NULL");
    string stk_name("(Stock(NULL))");
    if (sw.getSYS()) {
        name = sw.getSYS()->name();

        Stock stk = sw.getSYS()->getStock();
        if (!stk.isNull()) {
            stk_name = "(Stock(" + stk.market_code() + "))";
        }
    }

    os << "SystemWeight(sys: " << name << stk_name << ",  weight: " << sw.getWeight() << ")";

    os.unsetf(std::ostream::floatfield);
    os.precision();
    return os;
}

SystemWeight& SystemWeight::operator=(SystemWeight&& other) {
    if (this != &other) {
        m_sys = std::move(other.m_sys);
        m_weight = other.m_weight;
    }
    return *this;
}

} /* namespace stradex */
