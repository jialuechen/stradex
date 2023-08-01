#pragma once
#ifndef DATA_DRIVER_KDATATEMPCSVDRIVER_H_
#define DATA_DRIVER_KDATATEMPCSVDRIVER_H_

#include "../../KDataDriver.h"

namespace STRADEX {


class KDataTempCsvDriver : public KDataDriver {
public:
    KDataTempCsvDriver();
    KDataTempCsvDriver(const string& day_filename, const string& min_filename);
    virtual ~KDataTempCsvDriver();

    void setDayFileName(const string& day_filename) {
        m_day_filename = day_filename;
    }

    void setMinFileName(const string& min_filename) {
        m_min_filename = min_filename;
    }

    virtual KDataDriverPtr _clone() override {
        return std::make_shared<KDataTempCsvDriver>(m_day_filename, m_min_filename);
    }

    virtual bool isIndexFirst() override {
        return false;
    }

    virtual bool canParallelLoad() override {
        return false;
    }

    
    virtual size_t getCount(const string& market, const string& code, KQuery::KType kType) override;

    
    virtual bool getIndexRangeByDate(const string& market, const string& code, const KQuery& query,
                                     size_t& out_start, size_t& out_end) override;

    
    virtual KRecordList getKRecordList(const string& market, const string& code,
                                       const KQuery& query) override;

private:
    void _get_title_column(const string&);
    void _get_token(const string&);
    string _get_filename();

    KRecordList _getKRecordListByIndex(const string& market, const string& code, int64_t start_ix,
                                       int64_t end_ix, KQuery::KType kType);

private:
    string m_day_filename;
    string m_min_filename;

    enum COLUMN {
        DATE = 0,
        OPEN = 1,
        HIGH = 2,
        LOW = 3,
        CLOSE = 4,
        VOLUME = 5,
        AMOUNT = 6,
        LAST = 7
    };

    size_t m_column[LAST];
    vector<string> m_token_buf;
};

} 

#endif 
