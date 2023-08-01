/*
 * util.h
 *
 *  Created on: 2009-11-20
 *      Author: jialuechen
 */

#pragma once
#ifndef stradex_UTILIIES_UTIL_H_
#define stradex_UTILIIES_UTIL_H_

#include <string>

#ifndef stradex_API
#define stradex_API
#endif

namespace stradex {

/**
 * @ingroup Utilities
 * @{
 */

#if defined(_MSC_VER)
std::string stradex_API utf8_to_gb(const char* szinput);
std::string stradex_API utf8_to_gb(const std::string& szinput);
std::string stradex_API gb_to_utf8(const char* szinput);
std::string stradex_API gb_to_utf8(const std::string& szinput);
#else
std::string stradex_API utf8_to_gb(const std::string& szinput);
std::string stradex_API gb_to_utf8(const std::string& szinput);
#endif

#define UTF8ToGB utf8_to_gb
#define GBToUTF8 gb_to_utf8

/**
 * 四舍五入，ROUND_HALF_EVEN 银行家舍入法
 * @param number  待四舍五入的数据
 * @param ndigits 保留小数位数
 * @return 处理过的数据
 */
double stradex_API roundEx(double number, int ndigits = 0);

/**
 * 向上截取，如10.1截取后为11
 * @param number  待处理数据
 * @param ndigits 保留小数位数
 * @return 处理过的数据
 */
double stradex_API roundUp(double number, int ndigits = 0);

/**
 * 向下截取，如10.1截取后为10
 * @param number  待处理数据
 * @param ndigits 保留小数位数
 * @return 处理过的数据
 */
double stradex_API roundDown(double number, int ndigits = 0);

/** @} */
}  // namespace stradex

#endif /* stradex_UTILIIES_UTIL_H_ */
