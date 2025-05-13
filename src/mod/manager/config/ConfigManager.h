#pragma once

#include <ll/api/mod/NativeMod.h>
#include <string>

namespace structure_loader::manager {

class ConfigManager final {
public:
    struct MainConfig {
        int         version                                = 1;
        std::string defaultLocaleCode                      = "en_US";
        bool        logToConsoleIfStructureIsAlreadyLoaded = false;
        bool        backupRemovedStructure                 = true;
    };

    static bool              init(ll::mod::NativeMod& mod);
    static const MainConfig& getConfig();

private:
    static MainConfig config;
};

} // namespace structure_loader::manager