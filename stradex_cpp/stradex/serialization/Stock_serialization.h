/*
 * Stock_Serialization.h
 *
 *  Created on: 2013-4-29
 *      Author: jialuechen
 */

#pragma once
#ifndef STOCK_SERIALIZATION_H_
#define STOCK_SERIALIZATION_H_

#include "../config.h"
#include "../Stock.h"
#include "../utilities/util.h"

//===========================================================================
// 以下为Stock的序列化，目前仅实现了在StockManager中管理的Stock的序列化
// 注意，该段代码在namespace stradex之外
// TODO 实现非StockManager管理的Stock的序列化
//===========================================================================
#if stradex_SUPPORT_SERIALIZATION
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>

namespace boost {
namespace serialization {
template <class Archive>

void save(Archive& ar, const stradex::Stock& stock, unsigned int version) {
    stradex::string market_code = stock.market_code();
    stradex::string name = stock.name();
    ar& BOOST_SERIALIZATION_NVP(market_code);
    ar& BOOST_SERIALIZATION_NVP(name);
}

template <class Archive>
void load(Archive& ar, stradex::Stock& stock, unsigned int version) {
    stradex::string market_code, name;
    ar& BOOST_SERIALIZATION_NVP(market_code);
    ar& BOOST_SERIALIZATION_NVP(name);
    stock = stradex::getStock(market_code);
}
}  // namespace serialization
}  // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(stradex::Stock)

#endif /* stradex_SUPPORT_SERIALIZATION */

#endif /* STOCK_SERIALIZATION_H_ */
