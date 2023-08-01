#pragma once
#ifndef DATA_DRIVER_BLOCK_INFO_stradex_QLBLOCKINFODRIVER_H_
#define DATA_DRIVER_BLOCK_INFO_stradex_QLBLOCKINFODRIVER_H_

#include "../../BlockInfoDriver.h"

namespace stradex {

class QLBlockInfoDriver : public BlockInfoDriver {
public:
    QLBlockInfoDriver() : BlockInfoDriver("stradex"){};
    virtual ~QLBlockInfoDriver();

    virtual bool _init() override;
    virtual Block getBlock(const string&, const string&) override;
    virtual BlockList getBlockList(const string& category) override;
    virtual BlockList getBlockList() override;
};

} 

#endif 
