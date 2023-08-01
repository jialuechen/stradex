/*
 * export.cpp
 *
 *  Created on: 2013-4-29
 *      Author: jialuechen
 */

#include "../config.h"

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

#include "TradeManager.h"
#include "imp/TradeCostStub.h"
#include "imp/FixedATradeCost.h"
#include "imp/ZeroTradeCost.h"
#include "imp/FixedA2015TradeCost.h"
#include "imp/FixedA2017TradeCost.h"

BOOST_CLASS_EXPORT(stradex::TradeManager)
BOOST_CLASS_EXPORT(stradex::TradeManagerBase)
BOOST_CLASS_EXPORT(stradex::TradeCostStub)
BOOST_CLASS_EXPORT(stradex::FixedATradeCost)
BOOST_CLASS_EXPORT(stradex::ZeroTradeCost)
BOOST_CLASS_EXPORT(stradex::FixedA2015TradeCost)
BOOST_CLASS_EXPORT(stradex::FixedA2017TradeCost)

#endif /* stradex_SUPPORT_SERIALIZATION */
