# -*- coding: utf8 -*-

from stradex.util.slice import list_getitem
from stradex.cpp.core import SYS_Simple as cpp_SYS_Simple
from stradex.cpp.core import (
    System, SystemList, SystemWeight, SystemWeightList, ConditionBase, EnvironmentBase, MoneyManagerBase,
    ProfitGoalBase, SelectorBase, SignalBase, SlippageBase, StoplossBase
)

#------------------------------------------------------------------
# System
#------------------------------------------------------------------

System.Part.__doc__ = """
系统部件枚举值，系统的买入/卖出等操作可由这些部件触发，用于标识实际交易指令的来源，
参见：:py:class:`TradeRecord`。

实际使用中，可使用 System.ENVIRONMENT 的简化方式 代替 System.Part.ENVIRONMENT，
其他与此类似。

- System.Part.ENVIRONMENT  - 市场环境判断策略
- System.Part.CONDITION    - 系统有效条件
- System.Part.SIGNAL       - 信号指示器
- System.Part.STOPLOSS     - 止损策略
- System.Part.TAKEPROFIT   - 止盈策略
- System.Part.MONEYMANAGER - 资金管理策略
- System.Part.PROFITGOAL   - 盈利目标策略
- System.Part.SLIPPAGE     - 移滑价差算法
- System.Part.INVALID      - 无效值边界，大于等于该值时为无效部件
"""

System.ENVIRONMENT = System.Part.ENVIRONMENT
System.CONDITION = System.Part.CONDITION
System.SIGNAL = System.Part.SIGNAL
System.STOPLOSS = System.Part.STOPLOSS
System.TAKEPROFIT = System.Part.TAKEPROFIT
System.MONEYMANAGER = System.Part.MONEYMANAGER
System.PROFITGOAL = System.Part.PROFITGOAL
System.SLIPPAGE = System.Part.SLIPPAGE
System.INVALID = System.Part.INVALID

SystemList.__getitem__ = list_getitem
SystemList.__str__ = lambda self: str(list(self))
SystemList.__repr__ = lambda self: repr(list(self))


def SYS_Simple(tm=None, mm=None, ev=None, cn=None, sg=None, st=None, tp=None, pg=None, sp=None):
    sys_ins = cpp_SYS_Simple()
    if tm:
        sys_ins.tm = tm
    if mm:
        sys_ins.mm = mm
    if ev:
        sys_ins.ev = ev
    if cn:
        sys_ins.cn = cn
    if sg:
        sys_ins.sg = sg
    if st:
        sys_ins.st = st
    if tp:
        sys_ins.tp = tp
    if pg:
        sys_ins.pg = pg
    if sp:
        sys_ins.sp = sp
    return sys_ins


#------------------------------------------------------------------
# allocatefunds
#------------------------------------------------------------------

SystemWeightList.__getitem__ = list_getitem
SystemWeightList.__str__ = lambda self: str(list(self))
SystemWeightList.__repr__ = lambda self: repr(list(self))

#------------------------------------------------------------------
# condition
#------------------------------------------------------------------

ConditionBase.__init__.__doc__ = """
__init__(self[, name="ConditionBase"])
    
    初始化构造函数
        
    :param str name: 名称
"""


def cn_init(self, name, params):
    super(self.__class__, self).__init__(name)
    self._name = name
    self._params = params
    for k, v in params.items():
        self.set_param(k, v)


def crtCN(func, params={}, name='crtCN'):
    meta_x = type(name, (ConditionBase, ), {'__init__': cn_init})
    meta_x._clone = lambda self: meta_x(self._name, self._params)
    meta_x._calculate = func
    return meta_x(name, params)



EnvironmentBase.__init__.__doc__ = """
__init__(self[, name='EnvironmentBase'])
        
    :param str name: 名称
"""


def ev_init(self, name, params):
    super(self.__class__, self).__init__(name)
    self._name = name
    self._params = params
    for k, v in params.items():
        self.set_param(k, v)


def crtEV(func, params={}, name='crtEV'):
    
    meta_x = type(name, (EnvironmentBase, ), {'__init__': ev_init})
    meta_x._clone = lambda self: meta_x(self._name, self._params)
    meta_x._calculate = func
    return meta_x(name, params)

MoneyManagerBase.__init__.__doc__ = """
__init__(self[, name="MoneyManagerBase])
    
        
    :param str name: name
"""


def mm_init(self, name, params):
    super(self.__class__, self).__init__(name)
    self._name = name
    self._params = params
    for k, v in params.items():
        self.set_param(k, v)


def crtMM(func, params={}, name='crtMM'):
    
    meta_x = type(name, (MoneyManagerBase, ), {'__init__': mm_init})
    meta_x._clone = lambda self: meta_x(self._name, self._params)
    meta_x._calculate = func
    return meta_x(name, params)


#------------------------------------------------------------------
# profitgoal
#------------------------------------------------------------------

ProfitGoalBase.__init__.__doc__ = """
__init__(self[, name="ProfitGoalBase"])
    
    初始化构造函数
        
    :param str name: 名称
"""


def pg_init(self, name, params):
    super(self.__class__, self).__init__(name)
    self._name = name
    self._params = params
    for k, v in params.items():
        self.set_param(k, v)


def crtPG(func, params={}, name='crtPG'):
    
    meta_x = type(name, (ProfitGoalBase, ), {'__init__': pg_init})
    meta_x._clone = lambda self: meta_x(self._name, self._params)
    meta_x._calculate = func
    return meta_x(name, params)

SelectorBase.__init__.__doc__ = """
__init__(self[, name="SelectorBase])
    
    
        
    :param str name: name
"""

#------------------------------------------------------------------
# signal
#------------------------------------------------------------------

SignalBase.__init__.__doc__ = """
__init__(self[, name="SignalBase"])
    
    :param str name: 名称
"""


def sig_init(self, name, params):
    super(self.__class__, self).__init__(name)
    self._name = name
    self._params = params
    for k, v in params.items():
        self.set_param(k, v)


def crtSG(func, params={}, name='crtSG'):
   
    meta_x = type(name, (SignalBase, ), {'__init__': sig_init})
    meta_x._clone = lambda self: meta_x(self._name, self._params)
    meta_x._calculate = func
    return meta_x(name, params)


#------------------------------------------------------------------
# Selector
#------------------------------------------------------------------
def se_add_stock_list(self, stk_list, proto_sys):
    result = True
    for stk in stk_list:
        success = self.add_stock(stk, proto_sys)
        if not success:
            result = False
            break
    return result


SelectorBase.add_stock_list = se_add_stock_list

#------------------------------------------------------------------
# slippage
#------------------------------------------------------------------

SlippageBase.__init__.__doc__ = """
__init__(self[, name="SlippageBase"])
    
    初始化构造函数
        
    :param str name: 名称
"""


def sl_init(self, name, params):
    super(self.__class__, self).__init__(name)
    self._name = name
    self._params = params
    for k, v in params.items():
        self.set_param(k, v)


def crtSL(func, params={}, name='crtSL'):
    
    meta_x = type(name, (SlippageBase, ), {'__init__': sl_init})
    meta_x._clone = lambda self: meta_x(self._name, self._params)
    meta_x._calculate = func
    return meta_x(name, params)


#------------------------------------------------------------------
# stoploss
#------------------------------------------------------------------

StoplossBase.__init__.__doc__ = """
__init__(self[, name="StoplossBase"])
    
    :param str name: 名称
"""


def st_init(self, name, params):
    super(self.__class__, self).__init__(name)
    self._name = name
    self._params = params
    for k, v in params.items():
        self.set_param(k, v)


def crtST(func, params={}, name='crtST'):
   
    meta_x = type(name, (StoplossBase, ), {'__init__': st_init})
    meta_x._clone = lambda self: meta_x(self._name, self._params)
    meta_x._calculate = func
    return meta_x(name, params)
