/*
 * LoanRecord.h
 *
 *  Created on: 2013-5-24
 *      Author: jialuechen
 */

#pragma once
#ifndef LOANRECORD_H_
#define LOANRECORD_H_

#include "../DataType.h"
#include "../config.h"

#if stradex_SUPPORT_SERIALIZATION
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/split_member.hpp>
#endif

namespace stradex {

/**
 * 借款记录（融资记录）
 * @ingroup TradeManagerClass
 */
class stradex_API LoanRecord {
public:
    LoanRecord() : datetime(Null<Datetime>()), value(0.0) {}
    LoanRecord(const Datetime& datetime, price_t value) : datetime(datetime), value(value) {}

    Datetime datetime;
    price_t value;

#if stradex_SUPPORT_SERIALIZATION
private:
    friend class boost::serialization::access;
    template <class Archive>
    void save(Archive& ar, const unsigned int version) const {
        namespace bs = boost::serialization;
        stradex::uint64_t date_number = datetime.number();
        ar& bs::make_nvp("datetime", date_number);
        ar& BOOST_SERIALIZATION_NVP(value);
    }

    template <class Archive>
    void load(Archive& ar, const unsigned int version) {
        namespace bs = boost::serialization;
        stradex::uint64_t date_number;
        ar& bs::make_nvp("datetime", date_number);
        datetime = Datetime(date_number);
        ar& BOOST_SERIALIZATION_NVP(value);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
#endif
};

typedef vector<LoanRecord> LoanRecordList;

stradex_API std::ostream& operator<<(std::ostream&, const LoanRecord&);

} /* namespace stradex */

#if FMT_VERSION >= 90000
template <>
struct fmt::formatter<stradex::LoanRecord> : ostream_formatter {};
#endif

#endif /* LOANRECORD_H_ */
