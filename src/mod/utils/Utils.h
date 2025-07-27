#include <string>
#include <vector>

namespace structure_loader::utils {

std::string
strReplace(const std::string& originalStr, const std::string& whatNeedToReplace, const std::string& whatForReplace);

std::string strReplace(
    const std::string&              originalStr,
    const std::vector<std::string>& whatNeedToReplace,
    const std::vector<std::string>& whatForReplace
);

} // namespace structure_loader::utils