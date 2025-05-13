#pragma once

#include <ll/api/mod/NativeMod.h>

namespace structure_loader::manager {

class MainManager final {
public:
    static bool initManagers(ll::mod::NativeMod& mod);
};

} // namespace structure_loader::manager