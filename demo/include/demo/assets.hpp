#pragma once

#ifndef ASSETS_INSTALL_PREFIX
#error ASSETS_INSTALL_PREFIX is not defined
#endif

namespace assets
{
    const std::string path_of(const std::string& rpath)
    {
        return ASSETS_INSTALL_PREFIX + rpath;
    }
}
