#pragma once
#ifndef MYSQLBASEINFODRIVER_H_
#define MYSQLBASEINFODRIVER_H_

#include "../../../utilities/ConnectPool.h"
#include "../../../utilities/db_connect/mysql/MySQLConnect.h"
#include "../../BaseInfoDriver.h"

#if defined(_MSC_VER)
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif

namespace stradex {

class MySQLBaseInfoDriver : public BaseInfoDriver {
public:
    MySQLBaseInfoDriver();
    virtual ~MySQLBaseInfoDriver();

    virtual bool _init() override;
    virtual vector<StockInfo> getAllStockInfo() override;
    virtual vector<MarketInfo> getAllMarketInfo() override;
    virtual vector<StockTypeInfo> getAllStockTypeInfo() override;

    virtual StockWeightList getStockWeightList(const string& market, const string& code,
                                               Datetime start, Datetime end) override;
    virtual MarketInfo getMarketInfo(const string& market) override;
    virtual StockTypeInfo getStockTypeInfo(uint32_t type) override;
    virtual StockInfo getStockInfo(string market, const string& code) override;
    virtual std::unordered_set<Datetime> getAllHolidays() override;

private:
    ConnectPool<MySQLConnect>* m_pool;
};

} /* namespace stradex */

#endif /* MYSQLBASEINFODRIVER_H_ */
