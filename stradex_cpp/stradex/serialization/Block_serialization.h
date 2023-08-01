/*
 * Block_serialization.h
 *
 *  Created on: 2015年2月9日
 *      Author: jialuechen
 */

#pragma once
#ifndef BLOCK_SERIALIZATION_H_
#define BLOCK_SERIALIZATION_H_

#include "../config.h"
#include "../Block.h"

#if stradex_SUPPORT_SERIALIZATION
#include "Stock_serialization.h"

namespace boost {
namespace serialization {
template <class Archive>
void save(Archive& ar, const stradex::Block& blk, unsigned int version) {
    stradex::string category = blk.category();
    stradex::string name = blk.name();
    ar& boost::serialization::make_nvp("category", category);
    ar& boost::serialization::make_nvp("name", name);
    stradex::StockList stock_list;
    stock_list.reserve(blk.size());
    for (auto iter = blk.begin(); iter != blk.end(); ++iter) {
        stock_list.push_back(*iter);
    }
    ar& boost::serialization::make_nvp("stock_list", stock_list);
}

template <class Archive>
void load(Archive& ar, stradex::Block& blk, unsigned int version) {
    stradex::string category, name;
    ar& boost::serialization::make_nvp("category", category);
    ar& boost::serialization::make_nvp("name", name);
    stradex::StockList stock_list;
    ar& boost::serialization::make_nvp("stock_list", stock_list);
    blk.category(category);
    blk.name(name);
    for (auto iter = stock_list.begin(); iter != stock_list.end(); ++iter) {
        blk.add(*iter);
    }
}
}  // namespace serialization
}  // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(stradex::Block)

#endif /* stradex_SUPPORT_SERIALIZATION */

#endif /* BLOCK_SERIALIZATION_H_ */
