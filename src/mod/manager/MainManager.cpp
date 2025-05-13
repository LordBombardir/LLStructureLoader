#include "MainManager.h"
#include "config/ConfigManager.h"
#include "lang/LanguageManager.h"

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

} // namespace structure_loader::manager