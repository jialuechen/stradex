/*
 * LoanRecord.cpp
 *
 *  Created on: 2013-5-24
 *      Author: jialuechen
 */

#include "LoanRecord.h"

namespace stradex {

stradex_API std::ostream& operator<<(std::ostream& os, const LoanRecord& record) {
    os << std::fixed;
    os.precision(2);
    os << "LoanRecord(" << record.datetime << ", " << record.value << ")";
    os.unsetf(std::ostream::floatfield);
    os.precision();
    return os;
}

} /* namespace stradex */
