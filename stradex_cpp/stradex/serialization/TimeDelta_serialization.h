

#pragma once
#ifndef TIMEDELTA_SERIALIZATION_H_
#define TIMEDELTA_SERIALIZATION_H_

#include "../datetime/TimeDelta.h"
#include "../config.h"

#if stradex_SUPPORT_SERIALIZATION
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost {
namespace serialization {

template <class Archive>
void save(Archive& ar, const stradex::TimeDelta& td, unsigned int version) {
    int64_t ticks = td.ticks();
    ar& BOOST_SERIALIZATION_NVP(ticks);
}

template <class Archive>
void load(Archive& ar, stradex::TimeDelta& td, unsigned int version) {
    int64_t ticks;
    ar& BOOST_SERIALIZATION_NVP(ticks);
    td = stradex::TimeDelta(boost::posix_time::time_duration(0, 0, 0, ticks));
}

}  // namespace serialization
}  // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(stradex::TimeDelta)

#endif

#endif
