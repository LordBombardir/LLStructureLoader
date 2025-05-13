#include "StructureManager.h"
#include "../../Main.h"
#include <format>
#include <ll/api/service/Bedrock.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/storage/DBStorage.h>
#include <mc/world/level/storage/LevelStorage.h>

// Support only `mystructure`!!!
constexpr std::string_view STRUCTURE_ID = "mystructure";

namespace structure_loader::manager {

bool StructureManager::isStructureLoaded(const std::string& name) {
    optional_ref<Level> level = ll::service::getLevel();
    if (!level) {
        return false;
    }

    return level->getLevelStorage().hasKey(
        std::format("structuretemplate_{0}:{1}", STRUCTURE_ID, name),
        DBHelpers::Category::WorldFeature
    );
}

std::vector<std::string> StructureManager::getLoadedStructures() {
    optional_ref<Level> level = ll::service::getLevel();
    if (!level) {
        return {};
    }

    level->getLevelStorage().forEachKeyWithPrefix(
        "structuretemplate_",
        DBHelpers::Category::WorldFeature,
        [](std::string_view one, std::string_view two) -> void {
            Main::getInstance().getSelf().getLogger().info("One: {}", one);
            Main::getInstance().getSelf().getLogger().info("Two: {}", two);
        }
    );
    return {};
}

void StructureManager::loadStructure(const std::string& name, const CompoundTag& nbt) {
    optional_ref<Level> level = ll::service::getLevel();
    if (!level) {
        return;
    }

    level->getLevelStorage()
        .saveData(std::format("structuretemplate_{0}:{1}", STRUCTURE_ID, name), nbt, DBHelpers::Category::WorldFeature);
}

void StructureManager::removeStructure(const std::string& name) {
    optional_ref<Level> level = ll::service::getLevel();
    if (!level) {
        return;
    }

    level->getLevelStorage().deleteData(
        std::format("structuretemplate_{0}:{1}", STRUCTURE_ID, name),
        DBHelpers::Category::WorldFeature
    );
}

} // namespace structure_loader::manager