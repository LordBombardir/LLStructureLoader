#include "LoadStructureCommand.h"
#include "../utils/Utils.h"
#include "../manager/MainManager.h"
#include <mc/server/ServerPlayer.h>

namespace structure_loader::commands {

void LoadStructureCommand::execute(
    const CommandOrigin&            origin,
    CommandOutput&                  output,
    const Parameter&                parameter,
    [[maybe_unused]] const Command& command
) {
    std::string localeCode = origin.getEntity() == nullptr || !origin.getEntity()->isType(ActorType::Player)
                               ? manager::ConfigManager::getConfig().defaultLocaleCode
                               : static_cast<ServerPlayer&>(*origin.getEntity()).getLocaleCode();

    if (parameter.structureName.empty()) {
        output.error(manager::LanguageManager::getTranslate("commandLoadStructureUsing", localeCode));
        return;
    }

    if (!manager::MainManager::loadStructure(parameter.structureName)) {
        output.error(utils::strReplace(
            manager::LanguageManager::getTranslate("loadStructureError", localeCode),
            "{structureName}",
            parameter.structureName
        ));
        return;
    }

    output.success(utils::strReplace(
        manager::LanguageManager::getTranslate("loadStructureSuccess", localeCode),
        "{structureName}",
        parameter.structureName
    ));
}

void LoadStructureCommand::executeWithoutParameter(const CommandOrigin& origin, CommandOutput& output) {
    std::string localeCode = origin.getEntity() == nullptr || !origin.getEntity()->isType(ActorType::Player)
                               ? manager::ConfigManager::getConfig().defaultLocaleCode
                               : static_cast<ServerPlayer&>(*origin.getEntity()).getLocaleCode();

    output.error(manager::LanguageManager::getTranslate("commandLoadStructureUsing", localeCode));
}

} // namespace structure_loader::commands