#pragma once

#include <stdlib.h>
#include <string>

namespace stradex {

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#endif

inline std::string getUserHome() {
    char const *home = getenv("HOME");
    if (home) {
        return std::string(home);
    }

    home = getenv("USERPROFILE");
    if (home) {
        return std::string(home);
    }

    char const *hdrive = getenv("HOMEDRIVE");
    char const *hpath = getenv("HOMEPATH");
    if (hdrive && hpath) {
        return std::string(hdrive) + std::string(hpath);
    }

    return "";
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}  // namespace stradex