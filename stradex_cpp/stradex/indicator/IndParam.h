
#pragma once

#include "IndicatorImp.h"

namespace stradex {

class stradex_API Indicator;
class stradex_API IndicatorImp;

class stradex_API IndParam {
    stradex_API friend std::ostream& operator<<(std::ostream&, const IndParam&);

public:
    IndParam();
    explicit IndParam(const IndicatorImpPtr& ind);
    explicit IndParam(const Indicator& ind);

    IndicatorImpPtr getImp() const {
        return m_ind;
    }

    Indicator get() const;

private:
    IndicatorImpPtr m_ind;
};

}  // namespace stradex