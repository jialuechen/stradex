/*
 * MarketInfo.h
 *
 *  Created on: 2013-5-1
 *      Author: jialuechen
 */

#pragma once
#ifndef MARKETINFO_SERIALIZATION_H_
#define MARKETINFO_SERIALIZATION_H_

#include "../config.h"
#include "../MarketInfo.h"
#include "../utilities/util.h"

#if stradex_SUPPORT_SERIALIZATION
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include "TimeDelta_serialization.h"

namespace boost {
namespace serialization {

template <class Archive>
void save(Archive& ar, const stradex::MarketInfo& record, unsigned int version) {
    stradex::string market = record.market();
    stradex::string name = record.name();
    stradex::string description = record.description();
    stradex::string code = record.code();
    stradex::uint64_t lastDate = record.lastDate().number();
    stradex::TimeDelta openTime1 = record.openTime1();
    stradex::TimeDelta openTime2 = record.openTime2();
    stradex::TimeDelta closeTime1 = record.closeTime1();
    stradex::TimeDelta closeTime2 = record.closeTime2();
    ar& BOOST_SERIALIZATION_NVP(market);
    ar& BOOST_SERIALIZATION_NVP(name);
    ar& BOOST_SERIALIZATION_NVP(description);
    ar& BOOST_SERIALIZATION_NVP(code);
    ar& BOOST_SERIALIZATION_NVP(lastDate);
    ar& BOOST_SERIALIZATION_NVP(openTime1);
    ar& BOOST_SERIALIZATION_NVP(closeTime1);
    ar& BOOST_SERIALIZATION_NVP(openTime2);
    ar& BOOST_SERIALIZATION_NVP(closeTime2);
}

template <class Archive>
void load(Archive& ar, stradex::MarketInfo& record, unsigned int version) {
    stradex::string market, name, description, code;
    stradex::uint64_t lastDate;
    stradex::TimeDelta openTime1, openTime2, closeTime1, closeTime2;
    ar& BOOST_SERIALIZATION_NVP(market);
    ar& BOOST_SERIALIZATION_NVP(name);
    ar& BOOST_SERIALIZATION_NVP(description);
    ar& BOOST_SERIALIZATION_NVP(code);
    ar& BOOST_SERIALIZATION_NVP(lastDate);
    ar& BOOST_SERIALIZATION_NVP(openTime1);
    ar& BOOST_SERIALIZATION_NVP(closeTime1);
    ar& BOOST_SERIALIZATION_NVP(openTime2);
    ar& BOOST_SERIALIZATION_NVP(closeTime2);
    record = stradex::MarketInfo(market, name, description, code, stradex::Datetime(lastDate), openTime1,
                             closeTime1, openTime2, closeTime2);
}

}  // namespace serialization
}  // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(stradex::MarketInfo)

#endif /* stradex_SUPPORT_SERIALIZATION */

#endif /* MARKETINFO_SERIALIZATION_H_ */
