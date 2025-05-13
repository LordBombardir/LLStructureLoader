#pragma once

#include <ll/api/mod/NativeMod.h>
#include <string>

namespace structure_loader::manager {

class MainManager final {
public:
    static bool initManagers(ll::mod::NativeMod& mod);

    static void loadStructures(ll::mod::NativeMod& mod);

    static bool isStructureLoaded(const std::string& name);
    static bool loadStructure(const std::string& name);
    static bool removeStructure(const std::string& name);
};

} // namespace structure_loader::manager