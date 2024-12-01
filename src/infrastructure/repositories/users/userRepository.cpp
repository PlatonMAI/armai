#include "userRepository.hpp"

#include <exception>

namespace armai::infrastructure::repositories {

std::optional<int> UserRepository::getUserByEmail(const std::string&) const {
    throw new std::exception();
}

} // namespace armai::infrastructure::repositories
