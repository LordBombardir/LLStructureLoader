#include "CommandManager.h"
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/service/Bedrock.h>

namespace structure_loader::manager {

bool CommandManager::registerCommands() {
    // optional_ref<CommandRegistry> commandRegistry = ll::service::getCommandRegistry();
    // if (!commandRegistry) {
    //     return false;
    // }

    // std::vector<std::string> rankNames = {};
    // for (std::pair<std::string, object::Rank*> pair : RanksManager::getRanks()) {
    //     rankNames.push_back(pair.first);
    // }
    // ll::command::CommandRegistrar::getInstance().tryRegisterSoftEnum(std::string{structureEnumNames}, rankNames);

    // ll::command::CommandHandle& addRankCommand = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
    //     commands::AddRankCommand::getName(),
    //     commands::AddRankCommand::getDescription(),
    //     commands::AddRankCommand::getRequirement(),
    //     commands::AddRankCommand::getFlag()
    // );

    // for (const std::string& alias : commands::AddRankCommand::getAliases()) {
    //     addRankCommand.alias(alias);
    // }

    // addRankCommand.overload<commands::AddRankCommand::Parameter>()
    //     .required("rankName")
    //     .required("prefix")
    //     .required("chatFormat")
    //     .required("scoreTagFormat")
    //     .optional("inheritanceRank")
    //     .execute(&commands::AddRankCommand::execute);

    // addRankCommand.overload().execute(&commands::AddRankCommand::executeWithoutParameter);

    // ll::command::CommandHandle& setRankCommand = ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
    //     commands::SetRankCommand::getName(),
    //     commands::SetRankCommand::getDescription(),
    //     commands::SetRankCommand::getRequirement(),
    //     commands::SetRankCommand::getFlag()
    // );

    // for (const std::string& alias : commands::SetRankCommand::getAliases()) {
    //     setRankCommand.alias(alias);
    // }

    // setRankCommand.overload<commands::SetRankCommand::Parameter>()
    //     .required("player")
    //     .required("rankName")
    //     .execute(&commands::SetRankCommand::execute);

    // setRankCommand.overload().execute(&commands::SetRankCommand::executeWithoutParameter);
    return true;
}

void CommandManager::addStructureNameToSoftEnum(const std::string& structureName) {
    ll::command::CommandRegistrar::getInstance().addSoftEnumValues(std::string{structureEnumNames}, {structureName});
}

void CommandManager::removeStructureNameFromSoftEnum(const std::string& structureName) {
    ll::command::CommandRegistrar::getInstance().removeSoftEnumValues(std::string{structureEnumNames}, {structureName});
}

} // namespace structure_loader::manager