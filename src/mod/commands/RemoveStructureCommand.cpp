#include "RemoveStructureCommand.h"
#include "../Utils.hpp"
#include "../manager/MainManager.h"
#include <mc/server/ServerPlayer.h>

namespace structure_loader::commands {

void RemoveStructureCommand::execute(
    const CommandOrigin&            origin,
    CommandOutput&                  output,
    const Parameter&                parameter,
    [[maybe_unused]] const Command& command
) {
    std::string localeCode = origin.getEntity() == nullptr || !origin.getEntity()->isType(ActorType::Player)
                               ? manager::ConfigManager::getConfig().defaultLocaleCode
                               : static_cast<ServerPlayer&>(*origin.getEntity()).getLocaleCode();

    if (parameter.structureName.empty()) {
        output.error(manager::LanguageManager::getTranslate("commandRemoveStructureUsing", localeCode));
        return;
    }

    if (!manager::MainManager::removeStructure(parameter.structureName)) {
        output.error(Utils::strReplace(
            manager::LanguageManager::getTranslate("removeStructureError", localeCode),
            "{structureName}",
            parameter.structureName
        ));
        return;
    }

    output.success(Utils::strReplace(
        manager::LanguageManager::getTranslate("removeStructureSuccess", localeCode),
        "{structureName}",
        parameter.structureName
    ));
}

void RemoveStructureCommand::executeWithoutParameter(const CommandOrigin& origin, CommandOutput& output) {
    std::string localeCode = origin.getEntity() == nullptr || !origin.getEntity()->isType(ActorType::Player)
                               ? manager::ConfigManager::getConfig().defaultLocaleCode
                               : static_cast<ServerPlayer&>(*origin.getEntity()).getLocaleCode();

    output.error(manager::LanguageManager::getTranslate("commandRemoveStructureUsing", localeCode));
}

} // namespace structure_loader::commands