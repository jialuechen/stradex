#pragma once
#ifndef DATADRIVERFACTORY_H_
#define DATADRIVERFACTORY_H_

#include "DriverConnectPool.h"
#include "BaseInfoDriver.h"
#include "KDataDriver.h"
#include "BlockInfoDriver.h"

namespace stradex {

typedef DriverConnectPool<KDataDriverConnect> KDataDriverConnectPool;
typedef shared_ptr<KDataDriverConnectPool> KDataDriverConnectPoolPtr;


class stradex_API DataDriverFactory {
public:
    
    static void init();
    static void release();

    static void regBaseInfoDriver(const BaseInfoDriverPtr &);
    static void removeBaseInfoDriver(const string &name);
    static BaseInfoDriverPtr getBaseInfoDriver(const Parameter &);

    static void regBlockDriver(const BlockInfoDriverPtr &);
    static void removeBlockDriver(const string &name);
    static BlockInfoDriverPtr getBlockDriver(const Parameter &);

    static void regKDataDriver(const KDataDriverPtr &);
    static void removeKDataDriver(const string &name);
    static KDataDriverConnectPoolPtr getKDataDriverPool(const Parameter &);

private:
    static map<string, BaseInfoDriverPtr> *m_baseInfoDrivers;
    static map<string, BlockInfoDriverPtr> *m_blockDrivers;
    static map<string, KDataDriverPtr> *m_kdataPrototypeDrivers;        
    static map<string, KDataDriverConnectPoolPtr> *m_kdataDriverPools;  
};

} 
#endif 
