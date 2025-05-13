#include "Main.h"
#include "manager/MainManager.h"
#include "manager/command/CommandManager.h"
#include "manager/lang/LanguageManager.h"
#include "manager/structure/StructureManager.h"
#include <ll/api/mod/RegisterHelper.h>

namespace structure_loader {

Main& Main::getInstance() {
    static Main instance;
    return instance;
}

bool Main::load() {
    getSelf().getLogger().info("The mod is loading...");

    if (!manager::MainManager::initManagers(getSelf())) {
        getSelf().getLogger().info("Failed to load the mod!");
        return false;
    }

    getSelf().getLogger().info("The mod has been successfully loaded!");
    return true;
}

bool Main::enable() {
    getSelf().getLogger().info("The mod is enabling...");

    if (!manager::CommandManager::registerCommands()) {
        getSelf().getLogger().info("Failed to enable the mod!");
        return false;
    }

    getSelf().getLogger().info(
        "The mod has been successfully enabled! Choosed language: "
        + manager::LanguageManager::getTranslate("languageName")
    );

    manager::StructureManager::getLoadedStructures();

    getSelf().getLogger().info("Author: vk.com/lordbomba");
    return true;
}

bool Main::disable() {
    getSelf().getLogger().info("The mod is disabling...");

    getSelf().getLogger().info("The mod has been successfully disabled.");
    return true;
}

bool Main::unload() {
    getSelf().getLogger().info("The mod is unloading...");

    getSelf().getLogger().info("The mod has been successfully unloaded.");
    return true;
}

} // namespace structure_loader

LL_REGISTER_MOD(structure_loader::Main, structure_loader::Main::getInstance());
