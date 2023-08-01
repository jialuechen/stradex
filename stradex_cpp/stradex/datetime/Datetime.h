#pragma once
#ifndef DATETIME_H_
#define DATETIME_H_

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <chrono>
#include <string>
#include <vector>
#include <fmt/ostream.h>
#include "TimeDelta.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif

#ifndef stradex_API
#define stradex_API
#endif

namespace stradex {

namespace bt = boost::posix_time;
namespace bd = boost::gregorian;

class stradex_API Datetime {
public:
    static Datetime min();

    static Datetime max();

    static Datetime now();

    static Datetime today();

    
    static Datetime fromHex(uint64_t time);

public:
    Datetime();

    Datetime(const Datetime&);

    Datetime(long year, long month, long day, long hh = 0, long mm = 0, long sec = 0,
             long millisec = 0, long microsec = 0);

    
    explicit Datetime(const bd::date&);

   
    explicit Datetime(const bt::ptime&);

    
    explicit Datetime(unsigned long long);

    
    explicit Datetime(const std::string&);

    Datetime& operator=(const Datetime&);

    
    long year() const;


    long month() const;

    /** 日 [1, 31]，如果是 Null 将抛出异常 */
    long day() const;

    long hour() const;

    
    long minute() const;

    long second() const;

   
    long millisecond() const;

   
    long microsecond() const;

    
    bool isNull() const;

    
    Datetime operator+(TimeDelta d) const;

   
    Datetime operator-(TimeDelta d) const;

    
    uint64_t number() const noexcept;

    
    uint64_t hex() const noexcept;

    
    std::string str() const;

    
    std::string repr() const;

    bt::ptime ptime() const;

    bd::date date() const;

    std::time_t to_time_t() const;

    int dayOfWeek() const;

    int dayOfYear() const;

    Datetime startOfDay() const;

    Datetime endOfDay() const;

    Datetime dateOfWeek(int day) const;

    Datetime startOfWeek() const;

    Datetime endOfWeek() const;

    Datetime startOfMonth() const;

    Datetime endOfMonth() const;

    Datetime startOfQuarter() const;

    Datetime endOfQuarter() const;

    Datetime startOfHalfyear() const;

    Datetime endOfHalfyear() const;

    Datetime startOfYear() const;

    Datetime endOfYear() const;

    Datetime nextDay() const;

    Datetime nextWeek() const;

    Datetime nextMonth() const;

    Datetime nextQuarter() const;

    Datetime nextHalfyear() const;

    Datetime nextYear() const;

    Datetime preDay() const;

    Datetime preWeek() const;

    Datetime preMonth() const;

    Datetime preQuarter() const;

    Datetime preHalfyear() const;

    Datetime preYear() const;

private:
    bt::ptime m_data;
};

stradex_API std::ostream& operator<<(std::ostream&, const Datetime&);


typedef std::vector<Datetime> DatetimeList;

DatetimeList stradex_API getDateRange(const Datetime& start, const Datetime& end);
bool operator==(const Datetime&, const Datetime&);
bool operator!=(const Datetime&, const Datetime&);
bool operator>(const Datetime&, const Datetime&);
bool operator<(const Datetime&, const Datetime&);
bool operator>=(const Datetime&, const Datetime&);
bool operator<=(const Datetime&, const Datetime&);

inline bool operator==(const Datetime& d1, const Datetime& d2) {
    return d1.ptime() == d2.ptime();
}

inline bool operator!=(const Datetime& d1, const Datetime& d2) {
    return d1.ptime() != d2.ptime();
}

inline bool operator>(const Datetime& d1, const Datetime& d2) {
    return d1.ptime() > d2.ptime();
}

inline bool operator<(const Datetime& d1, const Datetime& d2) {
    return d1.ptime() < d2.ptime();
}

inline bool operator>=(const Datetime& d1, const Datetime& d2) {
    return d1.ptime() >= d2.ptime();
}

inline bool operator<=(const Datetime& d1, const Datetime& d2) {
    return d1.ptime() <= d2.ptime();
}

inline Datetime operator+(const TimeDelta& delta, const Datetime& date) {
    return date + delta;
}

inline TimeDelta operator-(const Datetime& d1, const Datetime& d2) {
    return TimeDelta(d1.ptime() - d2.ptime());
}



inline Datetime::Datetime() {
    bd::date d(bd::pos_infin);
    m_data = bt::ptime(d, bt::time_duration(0, 0, 0));
}

inline Datetime::Datetime(const Datetime& d) : m_data(d.m_data) {}

inline Datetime::Datetime(const bd::date& d) : m_data(bt::ptime(d, bt::time_duration(0, 0, 0))) {}

inline Datetime::Datetime(const bt::ptime& d) : m_data(d) {}

inline bt::ptime Datetime::ptime() const {
    return m_data;
}

inline bd::date Datetime::date() const {
    return m_data.date();
}

inline std::time_t Datetime::to_time_t() const {
    std::tm tt = bt::to_tm(m_data);
    return std::mktime(&tt);
}

inline int Datetime::dayOfWeek() const {
    return date().day_of_week();
}

inline int Datetime::dayOfYear() const {
    return date().day_of_year();
}

inline Datetime Datetime::startOfDay() const {
    return Datetime(date());
}

inline Datetime Datetime::operator+(TimeDelta d) const {
    return Datetime(m_data + d.time_duration());
}

inline Datetime Datetime::operator-(TimeDelta d) const {
    return Datetime(m_data - d.time_duration());
}

} /* namespace stradex */

namespace std {
template <>
class hash<stradex::Datetime> {
public:
    size_t operator()(stradex::Datetime const& d) const noexcept {
        return d.number();  // or use boost::hash_combine
    }
};
}  // namespace std

#if FMT_VERSION >= 90000
template <>
struct fmt::formatter<stradex::Datetime> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template <typename FormatContext>
    auto format(const stradex::Datetime& d, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{}", d.str());
    }
};
#endif

#endif /* DATETIME_H_ */
