/*
 * TimeLineRecord_serialization.h
 *
 *  Created on: 2019-2-11
 *      Author: jialuechen
 */

#pragma once
#ifndef TRANSRECORD_SERIALIZATION_H_
#define TRANSRECORD_SERIALIZATION_H_

#include "../config.h"
#include "../TransRecord.h"

#if stradex_SUPPORT_SERIALIZATION
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>

namespace boost {
namespace serialization {
template <class Archive>
void save(Archive& ar, const stradex::TransRecord& record, unsigned int version) {
    stradex::uint64_t datetime = record.datetime.number();
    ar& BOOST_SERIALIZATION_NVP(datetime);
    ar& make_nvp("price", record.price);
    ar& make_nvp("vol", record.vol);
    ar& make_nvp("direct", record.direct);
}

template <class Archive>
void load(Archive& ar, stradex::TransRecord& record, unsigned int version) {
    stradex::uint64_t datetime;
    ar& BOOST_SERIALIZATION_NVP(datetime);
    record.datetime = stradex::Datetime(datetime);
    ar& make_nvp("price", record.price);
    ar& make_nvp("vol", record.vol);
    ar& make_nvp("direct", record.direct);
}
}  // namespace serialization
}  // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(stradex::TransRecord)

#endif /* stradex_SUPPORT_SERIALIZATION */

#endif /* TRANSRECORD_SERIALIZATION_H_ */
