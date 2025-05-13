#include "CommandManager.h"
#include "../../commands/LoadStructureCommand.h"
#include "../../commands/RemoveStructureCommand.h"
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/service/Bedrock.h>

namespace structure_loader::manager {

bool CommandManager::registerCommands() {
    optional_ref<CommandRegistry> commandRegistry = ll::service::getCommandRegistry();
    if (!commandRegistry) {
        return false;
    }

    ll::command::CommandRegistrar::getInstance().tryRegisterSoftEnum(std::string{structureEnumNames}, {});

    ll::command::CommandHandle& loadStructureCommand = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
        commands::LoadStructureCommand::getName(),
        commands::LoadStructureCommand::getDescription(),
        commands::LoadStructureCommand::getRequirement(),
        commands::LoadStructureCommand::getFlag()
    );

    for (const std::string& alias : commands::LoadStructureCommand::getAliases()) {
        loadStructureCommand.alias(alias);
    }

    loadStructureCommand.overload<commands::LoadStructureCommand::Parameter>()
        .required("structureName")
        .execute(&commands::LoadStructureCommand::execute);

    loadStructureCommand.overload().execute(&commands::LoadStructureCommand::executeWithoutParameter);

    ll::command::CommandHandle& removeStructureCommand =
        ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
            commands::RemoveStructureCommand::getName(),
            commands::RemoveStructureCommand::getDescription(),
            commands::RemoveStructureCommand::getRequirement(),
            commands::RemoveStructureCommand::getFlag()
        );

    for (const std::string& alias : commands::RemoveStructureCommand::getAliases()) {
        removeStructureCommand.alias(alias);
    }

    removeStructureCommand.overload<commands::RemoveStructureCommand::Parameter>()
        .required("structureName")
        .execute(&commands::RemoveStructureCommand::execute);

    removeStructureCommand.overload().execute(&commands::RemoveStructureCommand::executeWithoutParameter);
    return true;
}

void CommandManager::addStructureNameToSoftEnum(const std::string& structureName) {
    ll::command::CommandRegistrar::getInstance().addSoftEnumValues(std::string{structureEnumNames}, {structureName});
}

void CommandManager::removeStructureNameFromSoftEnum(const std::string& structureName) {
    ll::command::CommandRegistrar::getInstance().removeSoftEnumValues(std::string{structureEnumNames}, {structureName});
}

} // namespace structure_loader::manager