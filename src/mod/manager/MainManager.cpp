#include "MainManager.h"
#include "../Main.h"
#include "../utils/Utils.h"
#include "command/CommandManager.h"
#include "config/ConfigManager.h"
#include "file/FileManager.h"
#include "lang/LanguageManager.h"
#include "structure/StructureManager.h"

namespace structure_loader::manager {

bool MainManager::initManagers(ll::mod::NativeMod& mod) {
    try {
        bool configInit = ConfigManager::init(mod);
        LanguageManager::init(mod);
        LanguageManager::addTranslations();

        return configInit;
    } catch (...) {
        return false;
    }
}

void MainManager::loadStructures(ll::mod::NativeMod& mod) {
    std::vector<std::filesystem::path> files =
        FileManager::getFilesInDirectory(mod.getDataDir() / "structures", ".mcstructure");

    for (const std::filesystem::path& path : files) {
        if (StructureManager::isStructureLoaded(path.stem().string())) {
            if (ConfigManager::getConfig().logToConsoleIfStructureIsAlreadyLoaded) {
                mod.getLogger().warn(utils::strReplace(
                    LanguageManager::getTranslate("structureAlreadyLoaded"),
                    "{structureName}",
                    path.stem().string()
                ));
            }

            std::filesystem::path newPath  = path;
            newPath                       += ".bak";
            FileManager::renameFile(path, newPath);
            continue;
        }

        std::string content = FileManager::getDataAsBytesFromFile(path);

        ll::Expected<CompoundTag> nbt = CompoundTag::fromBinaryNbt(content);
        if (!nbt) {
            mod.getLogger().warn(utils::strReplace(
                LanguageManager::getTranslate("badStructure"),
                {"{structureName}", "{errorMessage}"},
                {path.stem().string(), nbt.error().message()}
            ));
            continue;
        }

        StructureManager::loadStructure(path.stem().string(), nbt.value());

        std::filesystem::path newPath  = path;
        newPath                       += ".bak";
        FileManager::renameFile(path, newPath);

        CommandManager::addStructureNameToSoftEnum(path.stem().string());
    }
}

bool MainManager::isStructureLoaded(const std::string& name) { return StructureManager::isStructureLoaded(name); }

bool MainManager::loadStructure(const std::string& name) {
    if (StructureManager::isStructureLoaded(name)) {
        return false;
    }

    std::filesystem::path path = Main::getInstance().getSelf().getDataDir() / "structures" / (name + ".mcstructure");
    if (!FileManager::isFileExists(path)) {
        return false;
    }

    std::string content = FileManager::getDataAsBytesFromFile(path);

    ll::Expected<CompoundTag> nbt = CompoundTag::fromBinaryNbt(content);
    if (!nbt) {
        return false;
    }

    StructureManager::loadStructure(path.stem().string(), nbt.value());

    std::filesystem::path newPath  = path;
    newPath                       += ".bak";
    FileManager::renameFile(path, newPath);

    CommandManager::addStructureNameToSoftEnum(path.stem().string());
    return true;
}

bool MainManager::removeStructure(const std::string& name) {
    if (!StructureManager::isStructureLoaded(name)) {
        return false;
    }

    std::string nbt = StructureManager::removeStructure(name);
    if (nbt.empty()) {
        return false;
    }

    std::filesystem::path path = Main::getInstance().getSelf().getDataDir() / "structures" / (name + ".mcstructure");

    std::filesystem::path newPath  = path;
    newPath                       += ".bak";

    if (FileManager::isFileExists(path)) {
        if (ConfigManager::getConfig().backupRemovedStructure) {
            FileManager::renameFile(path, newPath);
        } else {
            FileManager::removeFile(path);
        }
    } else if (ConfigManager::getConfig().backupRemovedStructure) {
        FileManager::writeFile(newPath, nbt, true);
    }

    CommandManager::removeStructureNameFromSoftEnum(name);
    return true;
}

} // namespace structure_loader::manager