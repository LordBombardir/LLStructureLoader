#pragma once

#include <ll/api/command/EnumName.h>
#include <mc/server/commands/CommandFlag.h>
#include <mc/server/commands/CommandOrigin.h>
#include <string>

namespace structure_loader::manager {

class CommandManager final {
public:
    enum class StructureNames;
    static constexpr inline std::string_view structureEnumNames = ll::command::enum_name_v<StructureNames>;

    static bool registerCommands();
    static void addStructureNameToSoftEnum(const std::string& structureName);
    static void removeStructureNameFromSoftEnum(const std::string& structureName);
};

} // namespace structure_loader::manager