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

#include "imp/CrossSignal.h"
#include "imp/CrossGoldSignal.h"
#include "imp/SingleSignal.h"
#include "imp/SingleSignal2.h"
#include "imp/BoolSignal.h"

BOOST_CLASS_EXPORT(stradex::CrossSignal)
BOOST_CLASS_EXPORT(stradex::CrossGoldSignal)
BOOST_CLASS_EXPORT(stradex::SingleSignal)
BOOST_CLASS_EXPORT(stradex::SingleSignal2)
BOOST_CLASS_EXPORT(stradex::BoolSignal)

#endif /* stradex_SUPPORT_SERIALIZATION */
