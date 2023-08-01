#pragma once

#include "DBConnectBase.h"

namespace stradex {


void stradex_API DBUpgrade(const DBConnectPtr &driver, const char *module_name,
                       const std::vector<string> &upgrade_scripts, int start_version = 2,
                       const char *create_script = nullptr);

}  // namespace stradex