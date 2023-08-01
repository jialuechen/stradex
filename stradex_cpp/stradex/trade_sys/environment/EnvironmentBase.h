#pragma once
#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <set>
#include "../../KQuery.h"
#include "../../utilities/Parameter.h"
#include "../../utilities/util.h"

#if stradex_SUPPORT_SERIALIZATION
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/set.hpp>
#include "../../serialization/Datetime_serialization.h"
#include "../../serialization/KQuery_serialization.h"
#endif

namespace stradex {


class stradex_API EnvironmentBase : public enable_shared_from_this<EnvironmentBase> {
    PARAMETER_SUPPORT

public:
    EnvironmentBase();
    EnvironmentBase(const string& name);
    virtual ~EnvironmentBase();

    
    string name() const {
        return m_name;
    }

   
    void name(const string& name) {
        m_name = name;
    }

   
    void reset();


    void setQuery(const KQuery& query);


    KQuery getQuery() const {
        return m_query;
    }

    typedef shared_ptr<EnvironmentBase> EnvironmentPtr;
    
    EnvironmentPtr clone();

    void _addValid(const Datetime& datetime);

   
    bool isValid(const Datetime& datetime);

    virtual void _calculate() = 0;

    virtual void _reset() {}

    virtual EnvironmentPtr _clone() = 0;

protected:
    string m_name;
    KQuery m_query;
    std::set<Datetime> m_valid;

#if stradex_SUPPORT_SERIALIZATION
private:
    friend class boost::serialization::access;
    template <class Archive>
    void save(Archive& ar, const unsigned int version) const {
        ar& BOOST_SERIALIZATION_NVP(m_name);
        ar& BOOST_SERIALIZATION_NVP(m_params);
        // ev可能多个系统共享，保留m_query可能用于查错
        ar& BOOST_SERIALIZATION_NVP(m_query);
        ar& BOOST_SERIALIZATION_NVP(m_valid);
    }

    template <class Archive>
    void load(Archive& ar, const unsigned int version) {
        ar& BOOST_SERIALIZATION_NVP(m_name);
        ar& BOOST_SERIALIZATION_NVP(m_query);
        ar& BOOST_SERIALIZATION_NVP(m_valid);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
#endif /* stradex_SUPPORT_SERIALIZATION */
};

#if stradex_SUPPORT_SERIALIZATION
BOOST_SERIALIZATION_ASSUME_ABSTRACT(EnvironmentBase)
#endif

#if stradex_SUPPORT_SERIALIZATION
/**
 * 对于没有私有变量的继承子类，可直接使用该宏定义序列化
 * @code
 * class Drived: public EnvironmentBase {
 *     ENVIRONMENT_NO_PRIVATE_MEMBER_SERIALIZATION
 *
 * public:
 *     Drived();
 *     ...
 * };
 * @endcode
 * @ingroup Environment
 */
#define ENVIRONMENT_NO_PRIVATE_MEMBER_SERIALIZATION               \
private:                                                          \
    friend class boost::serialization::access;                    \
    template <class Archive>                                      \
    void serialize(Archive& ar, const unsigned int version) {     \
        ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(EnvironmentBase); \
    }
#else
#define ENVIRONMENT_NO_PRIVATE_MEMBER_SERIALIZATION
#endif


typedef shared_ptr<EnvironmentBase> EnvironmentPtr;
typedef shared_ptr<EnvironmentBase> EVPtr;

#define ENVIRONMENT_IMP(classname)              \
public:                                         \
    virtual EnvironmentPtr _clone() {           \
        return EnvironmentPtr(new classname()); \
    }                                           \
    virtual void _calculate();


stradex_API std::ostream& operator<<(std::ostream& os, const EnvironmentPtr&);
stradex_API std::ostream& operator<<(std::ostream& os, const EnvironmentBase&);

} /* namespace stradex */

#if FMT_VERSION >= 90000
template <>
struct fmt::formatter<stradex::EnvironmentBase> : ostream_formatter {};

template <>
struct fmt::formatter<stradex::EnvironmentPtr> : ostream_formatter {};
#endif

#endif /* ENVIRONMENT_H_ */
