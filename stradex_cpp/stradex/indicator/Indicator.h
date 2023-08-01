
#pragma once
#ifndef INDICATOR_H_
#define INDICATOR_H_

#include "IndicatorImp.h"
#include "IndParam.h"

namespace stradex {

#define IND_EQ_THRESHOLD 0.000001  
class stradex_API Indicator {
    stradex_API friend std::ostream& operator<<(std::ostream&, const Indicator&);

public:
    Indicator() {}
    Indicator(const IndicatorImpPtr& imp);
    Indicator(const Indicator& ind);
    Indicator(Indicator&& ind);
    virtual ~Indicator();

    Indicator& operator=(const Indicator&);
    Indicator& operator=(Indicator&&);

    /** 使用已有参数计算新值，返回全新的Indicator */
    Indicator operator()(const Indicator& ind);

    /** 生成新的克隆，并使用参数 k 作为新实例的上下文 */
    Indicator operator()(const KData& k);

    /** 生成新的克隆，同 clone */
    Indicator operator()();

    /** 指标名称 */
    string name() const;
    void name(const string& name);

    /** 返回形如：Name(param1_val,param2_val,...) */
    string long_name() const;

    /** 克隆操作 */
    Indicator clone() const;

    /** 设置上下文 */
    void setContext(const Stock&, const KQuery&);
    void setContext(const KData&);

    /** 获取上下文 */
    KData getContext() const;

    /** 显示指标公式 */
    string formula() const;

    /** 结果中需抛弃的个数 */
    size_t discard() const;

    /** 设置抛弃的个数，如果小于原有的discard则无效 */
    void setDiscard(size_t discard);

    /** 返回有几个结果集输出 */
    size_t getResultNumber() const;

    /** 判断是否为空 **/
    bool empty() const;

    /** 获取大小 **/
    size_t size() const;

    /** 只获取第一个结果集中相应位置输出，等同于get(pos, 0) */
    price_t operator[](size_t pos) const;

    /** 只获取第一个结果集中相应位置输出，等同于getByDate(date, 0) */
    price_t operator[](Datetime) const;

    /**
     * 获取第num个结果集中指定位置的数据
     * @param pos 结果集中的位置
     * @param num 第几个结果集
     */
    price_t get(size_t pos, size_t num = 0) const;

    /**
     * 获取指定位置的日期
     * @param pos 结果集中的位置
     */
    Datetime getDatetime(size_t pos) const;

    /**
     * 获取指定日期的数据
     * @param date 指定日期
     * @param num 第几个结果集
     */
    price_t getByDate(Datetime date, size_t num = 0) const;

    /** 获取指定日期相应的索引位置 */
    size_t getPos(Datetime) const;

    /**
     * 以指标的方式获取指定的结果集
     * @param num 指定的结果集
     */
    Indicator getResult(size_t num) const;

    /**
     * 以 PriceList 的方式获取指定的结果集
     * @param num 指定的结果集
     */
    PriceList getResultAsPriceList(size_t num) const;

    /**
     * 获取 DatetimeList
     */
    DatetimeList getDatetimeList() const;

    bool haveParam(const string& name) const {
        return m_imp ? m_imp->haveParam(name) : false;
    }

    template <typename ValueType>
    void setParam(const string& name, const ValueType& value) {
        if (m_imp) {
            m_imp->setParam<ValueType>(name, value);
        }
    }

    template <typename ValueType>
    ValueType getParam(const string& name) const {
        if (!m_imp) {
            throw std::out_of_range("out_of_range in Parameter::get : " + name);
        }
        return m_imp->getParam<ValueType>(name);
    }

    bool supportIndParam() const;
    bool haveIndParam(const string& name) const;
    void setIndParam(const string& name, const Indicator& ind);
    void setIndParam(const string& name, const IndParam& ind);
    IndParam getIndParam(const string& name) const;
    const IndicatorImpPtr getIndParamImp(const string& name) const;

    IndicatorImpPtr getImp() const {
        return m_imp;
    }

protected:
    IndicatorImpPtr m_imp;

#if stradex_SUPPORT_SERIALIZATION
private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& BOOST_SERIALIZATION_NVP(m_imp);
    }
#endif /* stradex_SUPPORT_SERIALIZATION */
};

inline string Indicator::name() const {
    return m_imp ? m_imp->name() : "IndicatorImp";
}

inline void Indicator::name(const string& name) {
    if (m_imp) {
        m_imp->name(name);
    }
}

inline string Indicator::long_name() const {
    return m_imp ? m_imp->long_name() : "IndicatorImp()";
}

inline size_t Indicator::discard() const {
    return m_imp ? m_imp->discard() : 0;
}

inline void Indicator::setDiscard(size_t discard) {
    if (m_imp) {
        m_imp->setDiscard(discard);
    }
}

inline size_t Indicator::getResultNumber() const {
    return m_imp ? m_imp->getResultNumber() : 0;
}

inline bool Indicator::empty() const {
    return (!m_imp || m_imp->size() == 0) ? true : false;
}

inline size_t Indicator::size() const {
    return m_imp ? m_imp->size() : 0;
}

inline Indicator Indicator::operator()() {
    return clone();
}

inline Indicator Indicator::clone() const {
    return m_imp ? Indicator(m_imp->clone()) : Indicator();
}

inline DatetimeList Indicator::getDatetimeList() const {
    return m_imp ? m_imp->getDatetimeList() : DatetimeList();
}

inline price_t Indicator::getByDate(Datetime date, size_t num) const {
    return m_imp ? m_imp->getByDate(date, num) : Null<price_t>();
}

inline price_t Indicator::operator[](size_t pos) const {
    return get(pos, 0);
}

inline price_t Indicator::get(size_t pos, size_t num) const {
    return m_imp->get(pos, num);
}

inline Datetime Indicator::getDatetime(size_t pos) const {
    return m_imp ? m_imp->getDatetime(pos) : Null<Datetime>();
}

inline size_t Indicator::getPos(Datetime date) const {
    return m_imp ? m_imp->getPos(date) : Null<size_t>();
}

inline price_t Indicator::operator[](Datetime date) const {
    return getByDate(date);
}

inline bool Indicator::haveIndParam(const string& name) const {
    return m_imp ? m_imp->haveIndParam(name) : false;
}

inline void Indicator::setIndParam(const string& name, const Indicator& ind) {
    if (m_imp) {
        m_imp->setIndParam(name, ind);
    }
}

inline void Indicator::setIndParam(const string& name, const IndParam& ind) {
    if (m_imp) {
        m_imp->setIndParam(name, ind);
    }
}

inline IndParam Indicator::getIndParam(const string& name) const {
    return m_imp ? m_imp->getIndParam(name) : IndParam();
}

inline const IndicatorImpPtr Indicator::getIndParamImp(const string& name) const {
    return m_imp ? m_imp->getIndParamImp(name) : IndicatorImpPtr();
}

inline bool Indicator::supportIndParam() const {
    return m_imp ? m_imp->supportIndParam() : false;
}

//--------------------------------------------------------------
// 指标操作
//-------------------------------------------------------------
stradex_API Indicator operator+(const Indicator&, const Indicator&);
stradex_API Indicator operator-(const Indicator&, const Indicator&);
stradex_API Indicator operator*(const Indicator&, const Indicator&);
stradex_API Indicator operator/(const Indicator&, const Indicator&);
stradex_API Indicator operator%(const Indicator&, const Indicator&);
stradex_API Indicator operator==(const Indicator&, const Indicator&);
stradex_API Indicator operator!=(const Indicator&, const Indicator&);
stradex_API Indicator operator>(const Indicator&, const Indicator&);
stradex_API Indicator operator<(const Indicator&, const Indicator&);
stradex_API Indicator operator>=(const Indicator&, const Indicator&);
stradex_API Indicator operator<=(const Indicator&, const Indicator&);
stradex_API Indicator operator&(const Indicator&, const Indicator&);
stradex_API Indicator operator|(const Indicator&, const Indicator&);

stradex_API Indicator operator+(const Indicator&, price_t);
stradex_API Indicator operator+(price_t, const Indicator&);

stradex_API Indicator operator-(const Indicator&, price_t);
stradex_API Indicator operator-(price_t, const Indicator&);

stradex_API Indicator operator*(const Indicator&, price_t);
stradex_API Indicator operator*(price_t, const Indicator&);

stradex_API Indicator operator/(const Indicator&, price_t);
stradex_API Indicator operator/(price_t, const Indicator&);

stradex_API Indicator operator%(const Indicator&, price_t);
stradex_API Indicator operator%(price_t, const Indicator&);

stradex_API Indicator operator==(const Indicator&, price_t);
stradex_API Indicator operator==(price_t, const Indicator&);

stradex_API Indicator operator!=(const Indicator&, price_t);
stradex_API Indicator operator!=(price_t, const Indicator&);

stradex_API Indicator operator>(const Indicator&, price_t);
stradex_API Indicator operator>(price_t, const Indicator&);

stradex_API Indicator operator<(const Indicator&, price_t);
stradex_API Indicator operator<(price_t, const Indicator&);

stradex_API Indicator operator>=(const Indicator&, price_t);
stradex_API Indicator operator>=(price_t, const Indicator&);

stradex_API Indicator operator<=(const Indicator&, price_t);
stradex_API Indicator operator<=(price_t, const Indicator&);

stradex_API Indicator operator&(const Indicator&, price_t);
stradex_API Indicator operator&(price_t, const Indicator&);

stradex_API Indicator operator|(const Indicator&, price_t);
stradex_API Indicator operator|(price_t, const Indicator&);

/**
 * 将ind1和ind2的结果组合在一起放在一个Indicator中。如ind = WEAVE(ind1, ind2)
 * 则此时ind包含多个结果，按ind1、ind2的顺序存放
 * @param ind1 指标1
 * @param ind2 指标2
 * @ingroup Indicator
 */
Indicator stradex_API WEAVE(const Indicator& ind1, const Indicator& ind2);

/**
 * 条件函数, 根据条件求不同的值。
 * @details
 * <pre>
 * 用法：IF(X,A,B)若X不为0则返回A,否则返回B
 * 例如：IF(CLOSE>OPEN,HIGH,LOW)表示该周期收阳则返回最高值,否则返回最低值
 * </pre>
 * @param x 条件指标
 * @param a 待选指标 a
 * @param b 待选指标 b
 * @ingroup Indicator
 */
Indicator stradex_API IF(const Indicator& x, const Indicator& a, const Indicator& b);
Indicator stradex_API IF(const Indicator& x, price_t a, const Indicator& b);
Indicator stradex_API IF(const Indicator& x, const Indicator& a, price_t b);
Indicator stradex_API IF(const Indicator& x, price_t a, price_t b);

} /* namespace stradex */

#if FMT_VERSION >= 90000
template <>
struct fmt::formatter<stradex::Indicator> : ostream_formatter {};
#endif

#endif /* INDICATOR_H_ */
