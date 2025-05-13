#pragma once

#include "../manager/lang/LanguageManager.h"
#include <mc/server/commands/Command.h>
#include <mc/server/commands/CommandFlag.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandPermissionLevel.h>

namespace structure_loader::commands {

class LoadStructureCommand {
public:
    struct Parameter {
        std::string structureName;
    };

    static std::string getName() { return "load-structure"; };
    static std::string getDescription() {
        return manager::LanguageManager::getTranslate("commandLoadStructureDescription");
    };
    static CommandPermissionLevel getRequirement() { return CommandPermissionLevel::GameDirectors; };
    static CommandFlag            getFlag() { return CommandFlagValue::NotCheat; };

    static std::vector<std::string> getAliases() { return {"structure-load"}; };

    static void execute(
        const CommandOrigin&            origin,
        CommandOutput&                  output,
        const Parameter&                parameter,
        [[maybe_unused]] const Command& command
    );
    static void executeWithoutParameter(const CommandOrigin& origin, CommandOutput& output);
};

} // namespace structure_loader::commands