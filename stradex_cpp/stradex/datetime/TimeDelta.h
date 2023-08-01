#pragma once
#ifndef stradex_DATETIME_TIMEDELTA_H
#define stradex_DATETIME_TIMEDELTA_H

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <cstdint>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <boost/date_time/posix_time/posix_time.hpp>

#ifndef stradex_API
#define stradex_API
#endif

namespace stradex {

namespace bt = boost::posix_time;
namespace bd = boost::gregorian;

/**
 * 时长，用于时间计算
 * @ingroup DataType
 */
class stradex_API TimeDelta {
public:
    explicit TimeDelta(int64_t days = 0, int64_t hours = 0, int64_t minutes = 0,
                       int64_t seconds = 0, int64_t milliseconds = 0, int64_t microseconds = 0);

    explicit TimeDelta(bt::time_duration td);

    TimeDelta(const TimeDelta&) = default;

    TimeDelta& operator=(const TimeDelta& other) {
        if (this != &other) {
            m_duration = other.m_duration;
        }
        return *this;
    }

    int64_t days() const;

    int64_t hours() const;

    int64_t minutes() const;

    int64_t seconds() const;

    int64_t milliseconds() const;

    int64_t microseconds() const;

    int64_t ticks() const {
        return m_duration.ticks();
    }

    double total_days() const {
        return double(ticks()) / 86400000000.0;
    }

    double total_hours() const {
        return double(ticks()) / 3600000000.0;
    }

    double total_minutes() const {
        return double(ticks()) / 60000000.0;
    }

    double total_seconds() const {
        return double(ticks()) / 1000000.0;
    }

    double total_milliseconds() const {
        return double(ticks()) / 1000.0;
    }

    bool isNegative() const {
        return m_duration.is_negative();
    }

    TimeDelta abs() const {
        return TimeDelta::fromTicks(std::abs(ticks()));
    }

    bt::time_duration time_duration() const {
        return m_duration;
    }

    std::string str() const {
#if FMT_VERSION >= 90000
        return fmt::format("{} days, {:0>2d}:{:0>2d}:{:<2.6f}", days(), hours(), minutes(),
                           seconds() + double(milliseconds() * 1000 + microseconds()) * 0.000001);
#else
        return fmt::format("{} days, {:>02d}:{:>02d}:{:<2.6f}", days(), hours(), minutes(),
                           seconds() + double(milliseconds() * 1000 + microseconds()) * 0.000001);
#endif
    }

    std::string repr() const {
        return fmt::format("TimeDelta({}, {}, {}, {}, {}, {})", days(), hours(), minutes(),
                           seconds(), milliseconds(), microseconds());
    }

    TimeDelta operator+(TimeDelta td) const {
        return TimeDelta(td.m_duration + m_duration);
    }


    TimeDelta operator-(TimeDelta td) const {
        return TimeDelta(m_duration - td.m_duration);
    }


    TimeDelta operator+() const {
        return *this;
    }

    /** - 号, 求负值，相当于 TimeDelta(0) 减自身 */
    TimeDelta operator-() const {
        return TimeDelta::fromTicks(-ticks());
    }

    /** 时长乘以系数，结果四舍五入 */
    TimeDelta operator*(double p) const;

    
    TimeDelta operator/(double p) const;

    /** 两个时长相除，求两者比例。如果除以零时长，将抛出 stradex::exception。 */
    double operator/(TimeDelta td) const;

    /** 地板除，小数点后直接截断 */
    TimeDelta floorDiv(double p) const;

    /** 两个时长相除求余。如果除以零时长，将抛出 stradex::exception。 */
    TimeDelta operator%(TimeDelta td) const;

    bool operator==(TimeDelta td) const {
        return m_duration == td.m_duration;
    }

    bool operator!=(TimeDelta td) const {
        return m_duration != td.m_duration;
    }

    bool operator>(TimeDelta td) const {
        return m_duration > td.m_duration;
    }

    bool operator<(TimeDelta td) const {
        return m_duration < td.m_duration;
    }

    bool operator>=(TimeDelta td) const {
        return m_duration >= td.m_duration;
    }

    bool operator<=(TimeDelta td) const {
        return m_duration <= td.m_duration;
    }

    /** 获取能够表达的最小值 TimeDelta(-99999999) */
    static TimeDelta min() {
        return TimeDelta(-99999999);
    }

    /** 获取能够表达的最大值 TimeDelta(99999999, 23, 59, 59, 999, 999) */
    static TimeDelta max() {
        return TimeDelta(99999999, 23, 59, 59, 999, 999);
    }

    /** 支持的最大 tick 数 */
    static int64_t maxTicks() {
        return m_max_micro_seconds;
    }

    /** 支持的最小 tick 数 */
    static int64_t minTicks() {
        return m_min_micro_seconds;
    }

    /** 获取表达精度 1 微秒, TimeDelta(0, 0, 0, 0, 0, 1) */
    static TimeDelta resolution() {
        return TimeDelta(0, 0, 0, 0, 0, 1);
    }

    /** 从 ticks 创建 */
    static TimeDelta fromTicks(int64_t ticks);

private:
    bt::time_duration m_duration;

    static constexpr const int64_t m_max_micro_seconds = 100000000LL * 24 * 60 * 60 * 1000000 - 1;
    static constexpr const int64_t m_min_micro_seconds = -99999999LL * 24 * 60 * 60 * 1000000;
    static constexpr const int64_t m_one_day_ticks = 24 * 60 * 60 * 1000000LL;
};

std::ostream& operator<<(std::ostream& out, TimeDelta td);
inline std::ostream& operator<<(std::ostream& out, TimeDelta td) {
    out << td.str();
    return out;
}

/**
 * TimeDelta 快捷创建函数
 * @param days 天数 [-99999999, 99999999]
 * @ingroup DataType
 */
TimeDelta Days(int64_t days);
inline TimeDelta Days(int64_t days) {
    return TimeDelta(days);
}

/**
 * TimeDelta 快捷创建函数
 * @param hours 小时数
 * @ingroup DataType
 */
TimeDelta stradex_API Hours(int64_t hours);

/**
 * TimeDelta 快捷创建函数
 * @param mins 分钟数
 * @ingroup DataType
 */
TimeDelta stradex_API Minutes(int64_t mins);

/**
 * TimeDelta 快捷创建函数
 * @param secs 秒数
 * @ingroup DataType
 */
TimeDelta stradex_API Seconds(int64_t secs);

/**
 * TimeDelta 快捷创建函数
 * @param milliseconds 毫秒数
 * @ingroup DataType
 */
TimeDelta stradex_API Milliseconds(int64_t milliseconds);

/**
 * TimeDelta 快捷创建函数
 * @param microsecs 微秒数
 * @ingroup DataType
 */
TimeDelta Microseconds(int64_t microsecs);
inline TimeDelta Microseconds(int64_t microsecs) {
    return TimeDelta::fromTicks(microsecs);
}

}

#if FMT_VERSION >= 90000
template <>
struct fmt::formatter<stradex::TimeDelta> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template <typename FormatContext>
    auto format(const stradex::TimeDelta& d, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{}", d.str());
    }
};
#endif

#endif