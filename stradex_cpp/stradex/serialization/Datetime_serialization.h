/*
 * Datetime_Serialization.h
 *
 *  Created on: 2013-4-29
 *      Author: jialuechen
 */

#pragma once
#ifndef DATETIME_SERIALIZATION_H_
#define DATETIME_SERIALIZATION_H_

#include "../datetime/Datetime.h"
#include "../config.h"

#if stradex_SUPPORT_SERIALIZATION
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost {
namespace serialization {
template <class Archive>
void save(Archive& ar, const stradex::Datetime& date, unsigned int version) {
    std::string datetime = date.str();
    ar& BOOST_SERIALIZATION_NVP(datetime);
}

template <class Archive>
void load(Archive& ar, stradex::Datetime& date, unsigned int version) {
    std::string datetime;
    ar& BOOST_SERIALIZATION_NVP(datetime);
    date = stradex::Datetime(datetime);
}
}  // namespace serialization
}  // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(stradex::Datetime)

#endif /* stradex_SUPPORT_SERIALIZATION */

#endif /* DATETIME_SERIALIZATION_H_ */
