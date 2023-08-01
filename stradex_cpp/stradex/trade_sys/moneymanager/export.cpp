/*
 * export.cpp
 *
 *  Created on: 2013-4-29
 *      Author: jialuechen
 */

#include "../../config.h"

#if stradex_SUPPORT_SERIALIZATION

#if stradex_SUPPORT_XML_ARCHIVE
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#endif /* stradex_SUPPORT_XML_ARCHIVE */

#if stradex_SUPPORT_TEXT_ARCHIVE
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#endif /* stradex_SUPPORT_TEXT_ARCHIVE */

#if stradex_SUPPORT_BINARY_ARCHIVE
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#endif /* stradex_SUPPORT_BINARY_ARCHIVE */

#include <boost/serialization/export.hpp>

#include "imp/FixedCountMoneyManager.h"
#include "imp/FixedPercentMoneyManager.h"
#include "imp/FixedRiskMoneyManager.h"
#include "imp/FixedCapitalMoneyManager.h"
#include "imp/FixedRatioMoneyManager.h"
#include "imp/FixedUnitsMoneyManager.h"
#include "imp/WilliamsFixedRiskMoneyManager.h"

BOOST_CLASS_EXPORT(stradex::FixedCountMoneyManager)
BOOST_CLASS_EXPORT(stradex::FixedPercentMoneyManager)
BOOST_CLASS_EXPORT(stradex::FixedRiskMoneyManager)
BOOST_CLASS_EXPORT(stradex::FixedCapitalMoneyManager)
BOOST_CLASS_EXPORT(stradex::FixedRatioMoneyManager)
BOOST_CLASS_EXPORT(stradex::FixedUnitsMoneyManager)
BOOST_CLASS_EXPORT(stradex::WilliamsFixedRiskMoneyManager)

#endif /* stradex_SUPPORT_SERIALIZATION */
