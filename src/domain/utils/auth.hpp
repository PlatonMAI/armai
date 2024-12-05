#include <string>

namespace armai::domain::utils::auth {

std::string getHashPassword(const std::string& password);
bool verifyPassword(const std::string& password, const std::string& hashPassword);

}
// namespace armai::domain::utils::auth
