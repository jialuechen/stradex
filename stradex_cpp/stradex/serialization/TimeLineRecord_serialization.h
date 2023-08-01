/*
 * TimeLineRecord_serialization.h
 *
 *  Created on: 2019-2-8
 *      Author: jialuechen
 */

#pragma once
#ifndef TIMELINERECORD_SERIALIZATION_H_
#define TIMELINERECORD_SERIALIZATION_H_

#include "../config.h"
#include "../TimeLineRecord.h"

#if stradex_SUPPORT_SERIALIZATION
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>

namespace boost {
namespace serialization {
template <class Archive>
void save(Archive& ar, const stradex::TimeLineRecord& record, unsigned int version) {
    stradex::uint64_t datetime = record.datetime.number();
    ar& BOOST_SERIALIZATION_NVP(datetime);
    ar& make_nvp("price", record.price);
    ar& make_nvp("vol", record.vol);
}

template <class Archive>
void load(Archive& ar, stradex::TimeLineRecord& record, unsigned int version) {
    stradex::uint64_t datetime;
    ar& BOOST_SERIALIZATION_NVP(datetime);
    record.datetime = stradex::Datetime(datetime);
    ar& make_nvp("price", record.price);
    ar& make_nvp("vol", record.vol);
}
}  // namespace serialization
}  // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(stradex::TimeLineRecord)

#endif /* stradex_SUPPORT_SERIALIZATION */

#endif /* TIMELINERECORD_SERIALIZATION_H_ */
