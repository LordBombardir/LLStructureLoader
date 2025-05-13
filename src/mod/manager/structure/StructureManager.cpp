#include "StructureManager.h"
#include <format>
#include <ll/api/service/Bedrock.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/storage/DBStorage.h>
#include <mc/world/level/storage/LevelStorage.h>

// Support only `mystructure`!!!
constexpr std::string_view STRUCTURE_ID = "mystructure";

namespace structure_loader::manager {

std::vector<std::string> StructureManager::getLoadedStructures() {
    optional_ref<Level> level = ll::service::getLevel();
    if (!level) {
        return {};
    }

    std::vector<std::string> loadedStructures = {};

    level->getLevelStorage().forEachKeyWithPrefix(
        "structuretemplate_",
        DBHelpers::Category::WorldFeature,
        [&loadedStructures](std::string_view key, [[maybe_unused]] std::string_view nbtData) -> void {
            if (!key.starts_with(STRUCTURE_ID)) {
                return;
            }

            loadedStructures.emplace_back(key.substr(STRUCTURE_ID.length() + 1));
        }
    );

    return loadedStructures;
}

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