#pragma once
#ifndef HISTORYFINANCEREADER_H_
#define HISTORYFINANCEREADER_H_

#include "../Stock.h"

namespace stradex {


class stradex_API HistoryFinanceReader {
public:
    HistoryFinanceReader() = delete;
    explicit HistoryFinanceReader(const string& dir);
    virtual ~HistoryFinanceReader();

    PriceList getHistoryFinanceInfo(Datetime date, const string& market, const string& code);

private:
    string m_dir;  
};

}  

#endif 
