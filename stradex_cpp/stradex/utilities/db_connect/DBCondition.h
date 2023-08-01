#pragma once

#include <string>
#include <ostream>
#include <sstream>
#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include "../../Log.h"

#ifndef stradex_API
#define stradex_API
#endif

namespace stradex {

struct ASC {
    ASC(const std::string& name) : name(name) {}
    std::string name;
};

struct DESC {
    DESC(const std::string& name) : name(name) {}
    std::string name;
};

class stradex_API DBCondition {
public:
    DBCondition() = default;
    DBCondition(const DBCondition&) = default;
    DBCondition(DBCondition&& rv) : m_condition(std::move(rv.m_condition)) {}

    explicit DBCondition(const char* cond) : m_condition(cond) {}
    explicit DBCondition(const std::string& cond) : m_condition(cond) {}

    DBCondition& operator=(const DBCondition&) = default;
    DBCondition& operator=(DBCondition&& rv) {
        if (this != &rv) {
            m_condition = std::move(rv.m_condition);
        }
        return *this;
    }

    DBCondition& operator&(const DBCondition& other);
    DBCondition& operator|(const DBCondition& other);

    enum ORDERBY { ORDER_ASC, ORDER_DESC };

    void orderBy(const std::string& field, ORDERBY order) {
        m_condition = order == ORDERBY::ORDER_ASC
                        ? fmt::format("{} order by {} ASC", m_condition, field)
                        : fmt::format("{} order by {} DESC", m_condition, field);
    }

    DBCondition& operator+(const ASC& asc) {
        orderBy(asc.name, ORDER_ASC);
        return *this;
    }

    DBCondition& operator+(const DESC& desc) {
        orderBy(desc.name, ORDER_ASC);
        return *this;
    }

    const std::string& str() const {
        return m_condition;
    }

private:
    std::string m_condition;
};

struct Field {
    Field(const std::string& name) : name(name) {}

    // in 和 not_in 不支持 字符串，一般不会用到 in ("stra", "strb") 的 SQL 操作
    template <typename T>
    DBCondition in(const std::vector<T>& vals) {
        stradex_CHECK(!vals.empty(), "input vals can't be empty!");
        return DBCondition(fmt::format("({} in ({}))", name, fmt::join(vals, ",")));
    }

    template <typename T>
    DBCondition not_in(const std::vector<T>& vals) {
        stradex_CHECK(!vals.empty(), "input vals can't be empty!");
        return DBCondition(fmt::format("({} not in ({}))", name, fmt::join(vals, ",")));
    }

    DBCondition like(const std::string& pattern) {
        return DBCondition(fmt::format(R"(({} like "{}"))", name, pattern));
    }

    DBCondition like(const char* pattern) {
        return DBCondition(fmt::format(R"(({} like "{}"))", name, pattern));
    }

    std::string name;
};

// linux下类成员函数模板特化必须放在类外实现
// 否则编译时会报：explicit specialization in non-namespace scope
template <>
inline DBCondition Field::in<std::string>(const std::vector<std::string>& vals) {
    stradex_CHECK(!vals.empty(), "input vals can't be empty!");
    std::ostringstream out;
    out << "(" << name << " in (";
    size_t total = vals.size();
    for (size_t i = 0; i < total - 1; i++) {
        out << "\"" << vals[i] << "\",";
    }
    out << "\"" << vals[total - 1] << "\"))";
    return DBCondition(out.str());
}

template <>
inline DBCondition Field::not_in<std::string>(const std::vector<std::string>& vals) {
    stradex_CHECK(!vals.empty(), "input vals can't be empty!");
    std::ostringstream out;
    out << "(" << name << " not in (";
    size_t total = vals.size();
    for (size_t i = 0; i < total - 1; i++) {
        out << "\"" << vals[i] << "\",";
    }
    out << "\"" << vals[total - 1] << "\"))";
    return DBCondition(out.str());
}

inline std::ostream& operator<<(std::ostream& out, const DBCondition& d) {
    out << d.str();
    return out;
}

template <typename T>
inline DBCondition operator==(const Field& field, T val) {
    std::ostringstream out;
    out << "(" << field.name << "=" << val << ")";
    return DBCondition(out.str());
}

template <typename T>
inline DBCondition operator!=(const Field& field, T val) {
    std::ostringstream out;
    out << "(" << field.name << "<>" << val << ")";
    return DBCondition(out.str());
}

template <typename T>
inline DBCondition operator>(const Field& field, T val) {
    std::ostringstream out;
    out << "(" << field.name << ">" << val << ")";
    return DBCondition(out.str());
}

template <typename T>
inline DBCondition operator>=(const Field& field, T val) {
    std::ostringstream out;
    out << "(" << field.name << ">=" << val << ")";
    return DBCondition(out.str());
}

template <typename T>
inline DBCondition operator<(const Field& field, T val) {
    std::ostringstream out;
    out << "(" << field.name << "<" << val << ")";
    return DBCondition(out.str());
}

template <typename T>
inline DBCondition operator<=(const Field& field, T val) {
    std::ostringstream out;
    out << "(" << field.name << "<=" << val << ")";
    return DBCondition(out.str());
}

template <>
inline DBCondition operator!=(const Field& field, const char* val) {
    return DBCondition(fmt::format(R"(({}<>"{}"))", field.name, val));
}

template <>
inline DBCondition operator>(const Field& field, const char* val) {
    return DBCondition(fmt::format(R"(({}>"{}"))", field.name, val));
}

template <>
inline DBCondition operator<(const Field& field, const char* val) {
    return DBCondition(fmt::format(R"(({}<"{}"))", field.name, val));
}

template <>
inline DBCondition operator>=(const Field& field, const char* val) {
    return DBCondition(fmt::format(R"(({}>="{}"))", field.name, val));
}

template <>
inline DBCondition operator<=(const Field& field, const char* val) {
    return DBCondition(fmt::format(R"(({}<="{}"))", field.name, val));
}

inline DBCondition operator==(const Field& field, const std::string& val) {
    return DBCondition(fmt::format(R"(({}="{}"))", field.name, val));
}

inline DBCondition operator!=(const Field& field, const std::string& val) {
    return DBCondition(fmt::format(R"(({}<>"{}"))", field.name, val));
}

inline DBCondition operator>(const Field& field, const std::string& val) {
    return DBCondition(fmt::format(R"(({}>"{}"))", field.name, val));
}

inline DBCondition operator<(const Field& field, const std::string& val) {
    return DBCondition(fmt::format(R"(({}<"{}"))", field.name, val));
}

inline DBCondition operator>=(const Field& field, const std::string& val) {
    return DBCondition(fmt::format(R"(({}>="{}"))", field.name, val));
}

inline DBCondition operator<=(const Field& field, const std::string& val) {
    return DBCondition(fmt::format(R"(({}<="{}"))", field.name, val));
}

inline DBCondition operator==(const Field& field, const char* val) {
    return DBCondition(fmt::format(R"(({}="{}"))", field.name, val));
}

}  // namespace stradex