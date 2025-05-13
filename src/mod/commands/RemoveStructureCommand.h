#pragma once

#include "../manager/command/CommandManager.h"
#include "../manager/lang/LanguageManager.h"
#include <ll/api/command/SoftEnum.h>
#include <mc/server/commands/Command.h>
#include <mc/server/commands/CommandFlag.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandPermissionLevel.h>

namespace structure_loader::commands {

class RemoveStructureCommand {
public:
    struct Parameter {
        ll::command::SoftEnum<manager::CommandManager::StructureNames> structureName;
    };

    static std::string getName() { return "remove-structure"; };
    static std::string getDescription() {
        return manager::LanguageManager::getTranslate("commandRemoveStructureDescription");
    };
    static CommandPermissionLevel getRequirement() { return CommandPermissionLevel::GameDirectors; };
    static CommandFlag            getFlag() { return CommandFlagValue::NotCheat; };

    static std::vector<std::string> getAliases() { return {"structure-remove"}; };

    static void execute(
        const CommandOrigin&            origin,
        CommandOutput&                  output,
        const Parameter&                parameter,
        [[maybe_unused]] const Command& command
    );
    static void executeWithoutParameter(const CommandOrigin& origin, CommandOutput& output);
};

} // namespace structure_loader::commands