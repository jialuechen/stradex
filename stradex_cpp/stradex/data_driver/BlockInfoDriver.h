#pragma once
#ifndef DATA_DRIVER_BLOCKINFODRIVER_H_
#define DATA_DRIVER_BLOCKINFODRIVER_H_

#include "../utilities/Parameter.h"
#include "../Block.h"

namespace stradex {


class stradex_API BlockInfoDriver {
    PARAMETER_SUPPORT

public:
    BlockInfoDriver(const string& name);
    virtual ~BlockInfoDriver(){};

   
    const string& name() const;

    bool init(const Parameter& params);

    
    virtual bool _init() = 0;


    virtual Block getBlock(const string& category, const string& name) = 0;

    
    virtual BlockList getBlockList(const string& category) = 0;

    
    virtual BlockList getBlockList() = 0;

private:
    bool checkType();

protected:
    string m_name;
};

typedef shared_ptr<BlockInfoDriver> BlockInfoDriverPtr;

stradex_API std::ostream& operator<<(std::ostream&, const BlockInfoDriver&);
stradex_API std::ostream& operator<<(std::ostream&, const BlockInfoDriverPtr&);

inline const string& BlockInfoDriver::name() const {
    return m_name;
}

} 
#endif 
