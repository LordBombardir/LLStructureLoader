#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

namespace structure_loader {

class Utils final {
public:
    static inline std::string fixPath(std::string path) {
        std::transform(path.begin(), path.end(), path.begin(), [](unsigned char c) -> int {
            return c == '\\' ? '/' : c;
        });
        return path;
    }

    static std::string strReplace(
        const std::string& originalStr,
        const std::string& whatNeedToReplace,
        const std::string& whatForReplace
    ) {
        std::string result = originalStr;

        size_t pos = 0;
        while ((pos = result.find(whatNeedToReplace, pos)) != std::string::npos) {
            result.replace(pos, whatNeedToReplace.length(), whatForReplace);
            pos += whatForReplace.length();
        }

        return result;
    }

    static std::string strReplace(
        const std::string&              originalStr,
        const std::vector<std::string>& whatNeedToReplace,
        const std::vector<std::string>& whatForReplace
    ) {
        std::string result = originalStr;
        if (whatNeedToReplace.size() != whatForReplace.size()) {
            throw std::invalid_argument("Vectors «whatNeedToReplace» and «whatForReplace» must have the same size!");
        }

        // Заменяем каждую подстроку
        for (size_t i = 0; i < whatNeedToReplace.size(); ++i) {
            const std::string& searchFor   = whatNeedToReplace[i];
            const std::string& replaceWith = whatForReplace[i];

            result = strReplace(result, searchFor, replaceWith);
        }

        return result;
    }
};

} // namespace structure_loader