#include "LanguageManager.h"
#include "../../Utils.hpp"
#include <LLTranslatorApi.h>
#include <memory>

namespace structure_loader::manager {

std::unique_ptr<ll::i18n::I18n> LanguageManager::i18n = nullptr;

void LanguageManager::init(ll::mod::NativeMod& mod) {
    i18n   = std::make_unique<ll::i18n::I18n>();
    auto _ = i18n->load(mod.getDataDir() / "languages");
}

std::string LanguageManager::getTranslate(const std::string_view& key, const std::string_view& localeCode) {
    return static_cast<std::string>(i18n->get(key, localeCode));
}

void LanguageManager::addTranslations() {
    ::setTranslationForCommandDescription(
        "load-structure",
        manager::LanguageManager::getTranslate("commandLoadStructureDescription", "ru_RU"),
        "ru_RU"
    );
    ::setTranslationForCommandDescription(
        "remove-structure",
        manager::LanguageManager::getTranslate("commandRemoveStructureDescription", "ru_RU"),
        "ru_RU"
    );
}

} // namespace structure_loader::manager