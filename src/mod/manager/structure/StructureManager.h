#pragma once

#include <mc/nbt/CompoundTag.h>
#include <string>
#include <vector>

namespace structure_loader::manager {

class StructureManager final {
public:
    static bool isStructureLoaded(const std::string& name);

    static std::vector<std::string> getLoadedStructures();

    static void loadStructure(const std::string& name, const CompoundTag& nbt);

    static void removeStructure(const std::string& name);
};

} // namespace structure_loader::manager