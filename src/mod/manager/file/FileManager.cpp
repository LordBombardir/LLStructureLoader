#include "FileManager.h"
#include <fstream>

namespace structure_loader::manager {

std::vector<std::filesystem::path>
FileManager::getFilesInDirectory(const std::filesystem::path& path, const std::optional<std::string>& checkExtension) {
    std::vector<std::filesystem::path> files;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            if (checkExtension != std::nullopt && entry.path().extension() != checkExtension.value()) {
                continue;
            }

            files.push_back(entry.path());
        }
    }
    return files;
}

std::string FileManager::getDataAsBytesFromFile(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file) {
        throw std::runtime_error("Couldn't open the file: " + path.string());
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string buffer(size, '\0');
    file.read(buffer.data(), size);
    return buffer;
}

void FileManager::renameFile(const std::filesystem::path& path, const std::filesystem::path& name) {
    std::filesystem::rename(path, name);
}

void FileManager::removeFile(const std::filesystem::path& path) { std::filesystem::remove(path); }

void FileManager::directoryEnsure(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directories(path);
    } else if (!std::filesystem::is_directory(path)) {
        throw std::runtime_error("The path exists, but it is not a directory: " + path.string());
    }
}

} // namespace structure_loader::manager