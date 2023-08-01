/*
 * KQuery.h
 *
 *  Created on: 2013-5-1
 *      Author: jialuechen
 */

#pragma once
#ifndef SERIALIZATION_KQUERY_H_
#define SERIALIZATION_KQUERY_H_

#include "../KQuery.h"
#include "../config.h"

#if stradex_SUPPORT_SERIALIZATION
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/base_object.hpp>

namespace boost {
namespace serialization {

template <class Archive>
void save(Archive& ar, const stradex::KQuery& query, unsigned int version) {
    stradex::string queryType, kType, recoverType;
    queryType = stradex::KQuery::getQueryTypeName(query.queryType());
    kType = stradex::KQuery::getKTypeName(query.kType());
    recoverType = stradex::KQuery::getRecoverTypeName(query.recoverType());
    ar& BOOST_SERIALIZATION_NVP(queryType);
    ar& BOOST_SERIALIZATION_NVP(kType);
    ar& BOOST_SERIALIZATION_NVP(recoverType);

    if (query.queryType() == stradex::KQuery::INDEX) {
        stradex::int64_t start = query.start();
        stradex::int64_t end = query.end();
        ar& BOOST_SERIALIZATION_NVP(start);
        ar& BOOST_SERIALIZATION_NVP(end);
    } else if (query.queryType() == stradex::KQuery::DATE) {
        stradex::uint64_t start = query.startDatetime().number();
        stradex::uint64_t end = query.endDatetime().number();
        ar& BOOST_SERIALIZATION_NVP(start);
        ar& BOOST_SERIALIZATION_NVP(end);
    } else {
        //非法忽略
    }
}

template <class Archive>
void load(Archive& ar, stradex::KQuery& query, unsigned int version) {
    stradex::string queryType, kType, recoverType;
    ar& BOOST_SERIALIZATION_NVP(queryType);
    ar& BOOST_SERIALIZATION_NVP(kType);
    ar& BOOST_SERIALIZATION_NVP(recoverType);

    stradex::KQuery::QueryType enum_query = stradex::KQuery::getQueryTypeEnum(queryType);
    stradex::KQuery::KType enmu_ktype = stradex::KQuery::getKTypeEnum(kType);
    stradex::KQuery::RecoverType enum_recover = stradex::KQuery::getRecoverTypeEnum(recoverType);

    if (enum_query == stradex::KQuery::INDEX) {
        stradex::int64_t start, end;
        ar& BOOST_SERIALIZATION_NVP(start);
        ar& BOOST_SERIALIZATION_NVP(end);
        query = stradex::KQuery(start, end, enmu_ktype, enum_recover);
    } else if (enum_query == stradex::KQuery::DATE) {
        stradex::uint64_t start, end;
        ar& BOOST_SERIALIZATION_NVP(start);
        ar& BOOST_SERIALIZATION_NVP(end);
        query =
          stradex::KQueryByDate(stradex::Datetime(start), stradex::Datetime(end), enmu_ktype, enum_recover);
    } else {
        //非法忽略
    }
}

}  // namespace serialization
}  // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(stradex::KQuery)

#endif /* stradex_SUPPORT_SERIALIZATION */

#endif /* SERIALIZATION_KQUERY_H_ */
