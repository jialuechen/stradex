/*
 * StockWeight.h
 *
 *  Created on: 2013-5-1
 *      Author: jialuechen
 */

#pragma once
#ifndef STOCKWEIGHT_SERIALIZATION_H_
#define STOCKWEIGHT_SERIALIZATION_H_

#include "../config.h"
#include "../StockWeight.h"

#if stradex_SUPPORT_SERIALIZATION
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>

namespace boost {
namespace serialization {
template <class Archive>
void save(Archive& ar, const stradex::StockWeight& record, unsigned int version) {
    stradex::uint64_t datetime = record.datetime().number();
    stradex::price_t countAsGift = record.countAsGift();
    stradex::price_t countForSell = record.countForSell();
    stradex::price_t priceForSell = record.priceForSell();
    stradex::price_t bonus = record.bonus();
    stradex::price_t increasement = record.increasement();
    stradex::price_t totalCount = record.totalCount();
    stradex::price_t freeCount = record.freeCount();
    ar& BOOST_SERIALIZATION_NVP(datetime);
    ar& BOOST_SERIALIZATION_NVP(countAsGift);
    ar& BOOST_SERIALIZATION_NVP(countForSell);
    ar& BOOST_SERIALIZATION_NVP(priceForSell);
    ar& BOOST_SERIALIZATION_NVP(bonus);
    ar& BOOST_SERIALIZATION_NVP(increasement);
    ar& BOOST_SERIALIZATION_NVP(totalCount);
    ar& BOOST_SERIALIZATION_NVP(freeCount);
}

template <class Archive>
void load(Archive& ar, stradex::StockWeight& record, unsigned int version) {
    stradex::uint64_t datetime;
    stradex::price_t countAsGift, countForSell, priceForSell, bonus;
    stradex::price_t increasement, totalCount, freeCount;
    ar& BOOST_SERIALIZATION_NVP(datetime);
    ar& BOOST_SERIALIZATION_NVP(countAsGift);
    ar& BOOST_SERIALIZATION_NVP(countForSell);
    ar& BOOST_SERIALIZATION_NVP(priceForSell);
    ar& BOOST_SERIALIZATION_NVP(bonus);
    ar& BOOST_SERIALIZATION_NVP(increasement);
    ar& BOOST_SERIALIZATION_NVP(totalCount);
    ar& BOOST_SERIALIZATION_NVP(freeCount);
    record = stradex::StockWeight(stradex::Datetime(datetime), countAsGift, countForSell, priceForSell,
                              bonus, increasement, totalCount, freeCount);
}
}  // namespace serialization
}  // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(stradex::StockWeight)

#endif /* stradex_SUPPORT_SERIALIZATION */

#endif /* STOCKWEIGHT_SERIALIZATION_H_ */
