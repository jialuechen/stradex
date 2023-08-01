#include <boost/python.hpp>
#include <stradex/trade_manage/Performance.h>

using namespace boost::python;
using namespace stradex;

void export_Performance() {
    class_<Performance>("Performance", "简单绩效统计", init<>())
      .def("reset", &Performance::reset, R"(reset(self)

        复位，清除已计算的结果)")

      .def("report", &Performance::report, (arg("tm"), arg("datetime") = Datetime::now()),
           R"(report(self, tm[, datetime=Datetime.now()])

        简单的文本统计报告，用于直接输出打印

        :param TradeManager tm: 指定的交易管理实例
        :param Datetime datetime: 统计截止时刻
        :rtype: str)")

      .def("statistics", &Performance::statistics, (arg("tm"), arg("datetime") = Datetime::now()),
           R"(statistics(self, tm[, datetime=Datetime.now()])

        根据交易记录，统计截至某一时刻的系统绩效, datetime必须大于等于lastDatetime

        :param TradeManager tm: 指定的交易管理实例
        :param Datetime datetime: 统计截止时刻)")

      .def("__getitem__", &Performance::get,
           R"(按指标名称获取指标值，必须在运行 statistics 或 report 之后生效
        
        :param str name: 指标名称
        :rtype: float))");
}
