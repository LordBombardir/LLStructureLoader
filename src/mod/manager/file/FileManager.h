#pragma once

#include <filesystem>
#include <ll/api/mod/NativeMod.h>
#include <optional>
#include <vector>

namespace structure_loader::manager {

class FileManager final {
public:
    static std::vector<std::filesystem::path> getFilesInDirectory(
        const std::filesystem::path&      path,
        const std::optional<std::string>& checkExtension = std::nullopt
    );

    static std::string getDataAsBytesFromFile(const std::filesystem::path& path);

    static bool isFileExists(const std::filesystem::path& path);
    static void renameFile(const std::filesystem::path& path, const std::filesystem::path& newPath);
    static void removeFile(const std::filesystem::path& path);
    static void writeFile(const std::filesystem::path& path, const std::string& data, bool isBinary);

private:
    static void directoryEnsure(const std::filesystem::path& path);
};

} // namespace structure_loader::manager