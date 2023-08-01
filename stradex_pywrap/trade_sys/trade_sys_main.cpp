#include <boost/python.hpp>

using namespace boost::python;

void export_Environment();
void export_Condition();
void export_MoneyManager();
void export_Signal();
void export_Stoploss();
void export_ProfitGoal();
void export_Slippage();
void export_System();
void export_Selector();
void export_Portfolio();
void export_AllocateFunds();

void export_trade_sys_main() {
    export_Environment();
    export_Condition();
    export_MoneyManager();
    export_Signal();
    export_Stoploss();
    export_ProfitGoal();
    export_Slippage();
    export_System();
    export_Selector();
    export_AllocateFunds();
    export_Portfolio();
}

