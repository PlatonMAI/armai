#include "userRepository.hpp"

#include <exception>

namespace armai::infrastructure::repositories {

std::optional<UserRepository::UserDomain> UserRepository::getUserByEmail(const std::string&) const {
    throw std::exception();
}
std::optional<UserRepository::UserDomain> UserRepository::getUserById(const int) const {
    throw std::exception();
}

int UserRepository::createUser(const UserRegisterCommand&) const {
    throw std::exception();
}

} // namespace armai::infrastructure::repositories
