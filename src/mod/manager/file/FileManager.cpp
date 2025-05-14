#include "FileManager.h"
#include <ll/api/io/FileUtils.h>

namespace structure_loader::manager {

std::vector<std::filesystem::path>
FileManager::getFilesInDirectory(const std::filesystem::path& path, const std::optional<std::string>& checkExtension) {
    directoryEnsure(path);

    std::vector<std::filesystem::path> files;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            if (checkExtension != std::nullopt && entry.path().extension() != checkExtension.value()) {
                continue;
            }

            files.emplace_back(entry.path());
        }
    }
    return files;
}

std::string FileManager::getDataAsBytesFromFile(const std::filesystem::path& path) {
    std::optional<std::string> data = ll::file_utils::readFile(path, true);
    if (!data.has_value()) {
        throw std::runtime_error("Couldn't open the file: " + path.generic_string());
    }

    return data.value();
}

bool FileManager::isFileExists(const std::filesystem::path& path) {
    return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}

void FileManager::renameFile(const std::filesystem::path& path, const std::filesystem::path& newPath) {
    if (std::filesystem::exists(newPath)) {
        throw std::runtime_error("The file already exists: " + newPath.generic_string());
    }

    std::filesystem::rename(path, newPath);
}

void FileManager::removeFile(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("The file does not exist: " + path.generic_string());
    }

    std::filesystem::remove(path);
}

void FileManager::writeFile(const std::filesystem::path& path, const std::string& data, bool isBinary) {
    if (std::filesystem::exists(path)) {
        throw std::runtime_error("The file already exists: " + path.generic_string());
    }

    ll::file_utils::writeFile(path, data, isBinary);
}

void FileManager::directoryEnsure(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directories(path);
    } else if (!std::filesystem::is_directory(path)) {
        throw std::runtime_error("The path exists, but it is not a directory: " + path.generic_string());
    }
}

} // namespace structure_loader::manager