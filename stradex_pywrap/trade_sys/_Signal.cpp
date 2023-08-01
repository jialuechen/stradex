#include <boost/python.hpp>
#include <stradex/trade_sys/signal/build_in.h>
#include "../_Parameter.h"
#include "../pickle_support.h"

using namespace boost::python;
using namespace stradex;

class SignalWrap : public SignalBase, public wrapper<SignalBase> {
public:
    SignalWrap() : SignalBase() {}
    SignalWrap(const string& name) : SignalBase(name) {}

    void _reset() {
        if (override func = this->get_override("_reset")) {
            func();
        } else {
            SignalBase::_reset();
        }
    }

    void default_reset() {
        this->SignalBase::_reset();
    }

    SignalPtr _clone() {
        return this->get_override("_clone")();
    }

    void _calculate() {
        this->get_override("_calculate")();
    }
};

string (SignalBase::*sg_get_name)() const = &SignalBase::name;
void (SignalBase::*sg_set_name)(const string&) = &SignalBase::name;

void export_Signal() {
    class_<SignalWrap, boost::noncopyable>("SignalBase", R"(信号指示器基类
    信号指示器负责产生买入、卖出信号。

公共参数：

    - alternate (bool|True) ：买入和卖出信号是否交替出现。单线型的信号通常通过拐点、斜率等判断信号的产生，此种情况下可能出现连续出现买入信号或连续出现卖出信号的情况，此时可通过该参数控制买入、卖出信号是否交替出现。而双线交叉型的信号通常本身买入和卖出已经是交替出现，此时该参数无效。

自定义的信号指示器接口：

    - _calculate : 【必须】子类计算接口
    - _clone : 【必须】克隆接口
    - _reset : 【可选】重载私有变量)",
                                           init<>())
      .def(init<const string&>())

      .def(self_ns::str(self))
      .def(self_ns::repr(self))

      .add_property("name", sg_get_name, sg_set_name, "名称")
      .add_property("to", &SignalBase::getTO, &SignalBase::setTO, "设置或获取交易对象")

      .def("get_param", &SignalBase::getParam<boost::any>, R"(get_param(self, name)

    获取指定的参数

    :param str name: 参数名称
    :return: 参数值
    :raises out_of_range: 无此参数)")

      .def("set_param", &SignalBase::setParam<object>, R"(set_param(self, name, value)

    设置参数

    :param str name: 参数名称
    :param value: 参数值
    :raises logic_error: Unsupported type! 不支持的参数类型)")

      .def("have_param", &SignalBase::haveParam, "是否存在指定参数")

      .def("should_buy", &SignalBase::shouldBuy, R"(should_buy(self, datetime)

    指定时刻是否可以买入

    :param Datetime datetime: 指定时刻
    :rtype: bool)")

      .def("should_sell", &SignalBase::shouldSell, R"(should_sell(self, datetime)

    指定时刻是否可以卖出

    :param Datetime datetime: 指定时刻
    :rtype: bool)")

      .def("next_time_should_buy", &SignalBase::nextTimeShouldBuy,
           R"(next_time_should_byu(self)

    下一时刻是否可以买入，相当于最后时刻是否指示买入)")

      .def("next_time_should_sell", &SignalBase::nextTimeShouldSell, R"(next_time_should_sell(self)
      
    下一时刻是否可以卖出，相当于最后时刻是否指示卖出)")

      .def("get_buy_signal", &SignalBase::getBuySignal, R"(get_buy_signal(self)

    获取所有买入指示日期列表
    
    :rtype: DatetimeList)")

      .def("get_sell_signal", &SignalBase::getSellSignal, R"(get_sell_signal(self)

    获取所有卖出指示日期列表

    :rtype: DatetimeList)")

      .def("_add_buy_signal", &SignalBase::_addBuySignal, R"(_add_buy_signal(self, datetime)

    加入买入信号，在_calculate中调用

    :param Datetime datetime: 指示买入的日期)")

      .def("_add_sell_signal", &SignalBase::_addSellSignal, R"(_add_sell_signal(self, datetime)

    加入卖出信号，在_calculate中调用

    :param Datetime datetime: 指示卖出的日期)")

      .def("reset", &SignalBase::reset, "复位操作")
      .def("clone", &SignalBase::clone, "克隆操作")
      .def("_calculate", pure_virtual(&SignalBase::_calculate), "【重载接口】子类计算接口")
      .def("_reset", &SignalBase::_reset, &SignalWrap::default_reset,
           "【重载接口】子类复位接口，复位内部私有变量")
      .def("_clone", pure_virtual(&SignalBase::_clone), "【重载接口】子类克隆接口")

#if stradex_PYTHON_SUPPORT_PICKLE
      .def_pickle(name_init_pickle_suite<SignalBase>())
#endif
      ;

    register_ptr_to_python<SignalPtr>();

    def("SG_Bool", SG_Bool, (arg("buy"), arg("sell"), arg("kpart") = "CLOSE"),
        R"(SG_Bool(buy, sell[, kpart='CLOSE'])

    布尔信号指示器，使用运算结果为类似bool数组的Indicator分别作为买入、卖出指示。

    :param Indicator buy: 买入指示（结果Indicator中相应位置>0则代表买入）
    :param Indicator sell: 卖出指示（结果Indicator中相应位置>0则代表卖出）
    :param string kpart: KDATA|OPEN|HIGH|LOW|CLOSE|AMO|VOL
    :return: 信号指示器)");

    def("SG_Single", SG_Single,
        (arg("ind"), arg("filter_n") = 10, arg("filter_p") = 0.1, arg("kpart") = "CLOSE"),
        R"(SG_Single(ind[, filter_n = 10, filter_p = 0.1, kpart='CLOSE'])
    
    生成单线拐点信号指示器。使用《精明交易者》 [BOOK1]_ 中给出的曲线拐点算法判断曲线趋势，公式见下::

        filter = percentage * STDEV((AMA-AMA[1], N)

        Buy  When AMA - AMA[1] > filter
        or Buy When AMA - AMA[2] > filter
        or Buy When AMA - AMA[3] > filter 
    
    :param Indicator ind:
    :param int filer_n: N日周期
    :param float filter_p: 过滤器百分比
    :param string kpart: KDATA|OPEN|HIGH|LOW|CLOSE|AMO|VOL
    :return: 信号指示器)");

    def("SG_Single2", SG_Single2,
        (arg("ind"), arg("filter_n") = 10, arg("filter_p") = 0.1, arg("kpart") = "CLOSE"),
        R"(SG_Single2(ind[, filter_n = 10, filter_p = 0.1, kpart='CLOSE'])
    
    生成单线拐点信号指示器2 [BOOK1]_::

        filter = percentage * STDEV((AMA-AMA[1], N)

        Buy  When AMA - @lowest(AMA,n) > filter
        Sell When @highest(AMA, n) - AMA > filter
    
    :param Indicator ind:
    :param int filer_n: N日周期
    :param float filter_p: 过滤器百分比
    :param string kpart: KDATA|OPEN|HIGH|LOW|CLOSE|AMO|VOL
    :return: 信号指示器)");

    def("SG_Cross", SG_Cross, (arg("fast"), arg("slow"), arg("kpart") = "CLOSE"),
        R"(SG_Cross(fast, slow[, kpart = "CLOSE"])

    双线交叉指示器，当快线从下向上穿越慢线时，买入；当快线从上向下穿越慢线时，卖出。如：5日MA上穿10日MA时买入，5日MA线下穿MA10日线时卖出:: 

        SG_Cross(OP(MA(n=10)), OP(MA(n=30)))

    :param Indicator fast: 快线
    :param Indicator slow: 慢线
    :param string kpart: OPEN|HIGH|LOW|CLOSE|AMO|VOL|KDATA
    :return: 信号指示器)");

    def("SG_CrossGold", SG_CrossGold, (arg("fast"), arg("slow"), arg("kpart") = "CLOSE"),
        R"(SG_CrossGold(fast, slow[, kpart = "CLOSE"])

    金叉指示器，当快线从下向上穿越慢线且快线和慢线的方向都是向上时为金叉，买入；
    当快线从上向下穿越慢线且快线和慢线的方向都是向下时死叉，卖出。::

        SG_CrossGold(OP(MA(n=10)), OP(MA(n=30)))

    :param Indicator fast: 快线
    :param Indicator slow: 慢线
    :param string kpart: OPEN|HIGH|LOW|CLOSE|AMO|VOL|KDATA
    :return: 信号指示器)");

    def("SG_Flex", SG_Flex, (arg("op"), arg("slow_n"), arg("kpart") = "CLOSE"),
        R"(SG_Flex(ind, slow_n[, kpart = 'CLOSE'])

    使用自身的EMA(slow_n)作为慢线，自身作为快线，快线向上穿越慢线买入，快线向下穿越慢线卖出。

    :param Indicator ind:
    :param int slow_n: 慢线EMA周期
    :param string kpart: KDATA|OPEN|HIGH|LOW|CLOSE|AMO|VOL
    :return: 信号指示器)");
}
