/*
 * KData.h
 *
 *  Created on: 2013-5-1
 *      Author: jialuechen
 */

#pragma once
#ifndef KDATA_SERIALIZATION_H_
#define KDATA_SERIALIZATION_H_

#include "../config.h"
#include "../KData.h"

#if stradex_SUPPORT_SERIALIZATION
#include "Stock_serialization.h"
#include "KQuery_serialization.h"

namespace boost {
namespace serialization {
template <class Archive>
void save(Archive& ar, const stradex::KData& kdata, unsigned int version) {
    stradex::Stock stock = kdata.getStock();
    stradex::KQuery query = kdata.getQuery();
    ar& BOOST_SERIALIZATION_NVP(stock);
    ar& BOOST_SERIALIZATION_NVP(query);
}

template <class Archive>
void load(Archive& ar, stradex::KData& kdata, unsigned int version) {
    stradex::Stock stock;
    stradex::KQuery query;
    ar& BOOST_SERIALIZATION_NVP(stock);
    ar& BOOST_SERIALIZATION_NVP(query);
    kdata = stock.isNull() ? stradex::KData() : stradex::KData(stock, query);
}

}  // namespace serialization
}  // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(stradex::KData)

#endif /* stradex_SUPPORT_SERIALIZATION */

#endif /* KDATA_SERIALIZATION_H_ */
