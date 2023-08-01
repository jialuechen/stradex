#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "MySQLBaseInfoDriver.h"

#include "../../../utilities/util.h"
#include "../../../StockManager.h"
#include "../../../Log.h"
#include "../table/MarketInfoTable.h"
#include "../table/StockTypeInfoTable.h"
#include "../table/StockWeightTable.h"
#include "../table/StockTable.h"
#include "../table/HolidayTable.h"

namespace stradex {

MySQLBaseInfoDriver::MySQLBaseInfoDriver() : BaseInfoDriver("mysql"), m_pool(nullptr) {}

MySQLBaseInfoDriver::~MySQLBaseInfoDriver() {
    if (m_pool) {
        delete m_pool;
    }
}

bool MySQLBaseInfoDriver::_init() {
    stradex_ASSERT_M(m_pool == nullptr, "Maybe repeat initialization!");
    Parameter connect_param;
    connect_param.set<string>("host", getParamFromOther<string>(m_params, "host", "127.0.0.1"));
    connect_param.set<string>("usr", getParamFromOther<string>(m_params, "usr", "root"));
    connect_param.set<string>("pwd", getParamFromOther<string>(m_params, "pwd", ""));
    connect_param.set<string>("db", getParamFromOther<string>(m_params, "db", "stradex_base"));
    string port_str = getParamFromOther<string>(m_params, "port", "3306");
    unsigned int port = boost::lexical_cast<unsigned int>(port_str);
    connect_param.set<int>("port", port);
    m_pool = new ConnectPool<MySQLConnect>(connect_param);
    stradex_CHECK(m_pool, "Failed malloc ConnectPool!");
    return true;
}

vector<MarketInfo> MySQLBaseInfoDriver::getAllMarketInfo() {
    vector<MarketInfo> result;
    stradex_ERROR_IF_RETURN(!m_pool, result, "Connect pool ptr is null!");

    try {
        auto con = m_pool->getConnect();
        vector<MarketInfoTable> infoTables;
        con->batchLoad(infoTables);
        for (auto &info : infoTables) {
            try {
                result.emplace_back(info.market(), info.name(), info.description(), info.code(),
                                    info.lastDate(), info.openTime1(), info.closeTime1(),
                                    info.openTime2(), info.closeTime2());
            } catch (std::exception &e) {
                stradex_ERROR("Failed load market, {}", e.what());
            } catch (...) {
                stradex_ERROR_UNKNOWN;
            }
        }

    } catch (std::exception &e) {
        stradex_FATAL("load Market table failed! {}", e.what());
    } catch (...) {
        stradex_FATAL("load Market table failed!");
    }

    return result;
}

vector<StockTypeInfo> MySQLBaseInfoDriver::getAllStockTypeInfo() {
    vector<StockTypeInfo> result;
    stradex_ERROR_IF_RETURN(!m_pool, result, "Connect pool ptr is null!");

    try {
        auto con = m_pool->getConnect();
        vector<StockTypeInfoTable> infoTables;
        con->batchLoad(infoTables);
        for (auto &info : infoTables) {
            result.emplace_back(info.type(), info.description(), info.tick(), info.tickValue(),
                                info.precision(), info.minTradeNumber(), info.maxTradeNumber());
        }

    } catch (std::exception &e) {
        stradex_FATAL("load StockTypeInfo table failed! {}", e.what());
    } catch (...) {
        stradex_FATAL("load StockTypeInfo table failed!");
    }

    return result;
}

StockWeightList MySQLBaseInfoDriver::getStockWeightList(const string &market, const string &code,
                                                        Datetime start, Datetime end) {
    StockWeightList result;
    stradex_ASSERT(m_pool);

    try {
        auto con = m_pool->getConnect();
        stradex_CHECK(con, "Failed fetch connect!");

        vector<StockWeightTable> table;
        Datetime new_end = end.isNull() ? Datetime::max() : end;
        con->batchLoad(
          table,
          format(
            "stockid=(select stockid from stock where marketid=(select marketid from "
            "market where market='{}') and code='{}') and date>={} and date<{} order by date asc",
            market, code, start.year() * 10000 + start.month() * 100 + start.day(),
            new_end.year() * 10000 + new_end.month() * 100 + new_end.day()));

        for (auto &w : table) {
            try {
                result.push_back(StockWeight(Datetime(w.date * 10000), w.countAsGift * 0.0001,
                                             w.countForSell * 0.0001, w.priceForSell * 0.001,
                                             w.bonus * 0.001, w.countOfIncreasement * 0.0001,
                                             w.totalCount, w.freeCount));
            } catch (std::out_of_range &e) {
                stradex_WARN("Date of id({}) is invalid! {}", w.id(), e.what());
            } catch (std::exception &e) {
                stradex_WARN("Error StockWeight Record id({}) {}", w.id(), e.what());
            } catch (...) {
                stradex_WARN("Error StockWeight Record id({})! Unknown reason!", w.id());
            }
        }

    } catch (std::exception &e) {
        stradex_FATAL("load StockWeight table failed! {}", e.what());
        return result;
    } catch (...) {
        stradex_FATAL("load StockWeight table failed!");
        return result;
    }

    return result;
}

vector<StockInfo> MySQLBaseInfoDriver::getAllStockInfo() {
    vector<StockInfo> result;
    stradex_ERROR_IF_RETURN(!m_pool, result, "Connect pool ptr is null!");
    try {
        auto con = m_pool->getConnect();
        con->batchLoad(result);
    } catch (...) {
    }
    return result;
}

StockInfo MySQLBaseInfoDriver::getStockInfo(string market, const string &code) {
    stradex_ASSERT(m_pool);
    StockInfo result;
    try {
        to_upper(market);
        auto con = m_pool->getConnect();
        string sql =
          format("{} and a.code='{}' and c.market='{}'", StockInfo::getSelectSQL(), code, market);
        SQLStatementPtr st = con->getStatement(sql);
        st->exec();
        if (st->moveNext()) {
            result.load(st);
        }
    } catch (...) {
    }
    return result;
}

MarketInfo MySQLBaseInfoDriver::getMarketInfo(const string &market) {
    MarketInfo result;
    stradex_ERROR_IF_RETURN(!m_pool, result, "Connect pool ptr is null!");
    auto con = m_pool->getConnect();
    try {
        MarketInfoTable info;
        string new_market(market);
        to_upper(new_market);
        con->load(info, format("market=\"{}\"", new_market));
        if (!info.market().empty()) {
            result = MarketInfo(info.market(), info.name(), info.description(), info.code(),
                                info.lastDate(), info.openTime1(), info.closeTime1(),
                                info.openTime2(), info.closeTime2());
        }
    } catch (...) {
    }
    return result;
}

StockTypeInfo MySQLBaseInfoDriver::getStockTypeInfo(uint32_t type) {
    StockTypeInfo result;
    stradex_ERROR_IF_RETURN(!m_pool, result, "Connect pool ptr is null!");
    auto con = m_pool->getConnect();
    try {
        StockTypeInfoTable info;
        con->load(info, format("type={}", type));
        if (info.type() != Null<uint32_t>()) {
            result = StockTypeInfo(info.type(), info.description(), info.tick(), info.tickValue(),
                                   info.precision(), info.minTradeNumber(), info.maxTradeNumber());
        }
    } catch (...) {
    }
    return result;
}

std::unordered_set<Datetime> MySQLBaseInfoDriver::getAllHolidays() {
    stradex_ASSERT(m_pool);
    std::unordered_set<Datetime> result;
    try {
        auto con = m_pool->getConnect();
        std::vector<HolidayTable> holidays;
        con->batchLoad(holidays);
        for (auto &holiday : holidays) {
            try {
                result.insert(holiday.datetime());
            } catch (std::exception &e) {
                stradex_WARN(e.what());
            } catch (...) {
                stradex_ERROR_UNKNOWN;
            }
        }
    } catch (...) {
    }
    return result;
}

} /* namespace stradex */
