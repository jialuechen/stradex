/*
 * BorrowRecord.cpp
 *
 *  Created on: 2013-5-2
 *      Author: jialuechen
 */

#include "BorrowRecord.h"

namespace stradex {

stradex_API std::ostream& operator<<(std::ostream& os, const BorrowRecord& bor) {
    string strip(", ");
    os << "BorrowRecord(" << bor.stock << strip << bor.number << strip << bor.value << strip << ")";
    return os;
}

BorrowRecord::BorrowRecord() : number(0), value(0.0) {}

BorrowRecord ::BorrowRecord(const Stock& stock, double number, price_t value)
: stock(stock), number(number), value(value) {}

} /* namespace stradex */
