<div align="center">
<img src="assets/stradex-logo.png" width="55%">
</div>

# Stradex: <font color="gold">Opti</font>mized <font color="gold">S</font>trategies, <font color="gold">Trad</font>ing and e<font color="gold">X</font>ecution in one package

Stradex is an asynchronous event-driven algorithmic trading framework built in Python (with C++ acceleration components). It is created to support live trading based on Interactive Brokers TWS API.

Stradex intergrates support for creating trading strategies, backtesting, market impact / slippage modeling as well as risk management through built-in algorithm controls.

## Installation
```
pip install --upgrade stradex
```

## Required Software
+ Latest Interactive Brokers Trader Workstation or IB Gateway(If you want to try paper/live trading). Make sure the API port is enabled.

## Required Third-Party Python Library
+ ibapi (please follow the official installation guide on Interactive Brokers website. Personal recommended choice is to run its setup.py to install it as a regular library)
+ pandas
+ numpy
+ matplotlib
+ psycopg2
+ TA-Lib

## License
stradex is licensed under [Apache-2.0](https://www.apache.org/licenses/LICENSE-2.0.txt).
