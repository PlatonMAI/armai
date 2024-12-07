#include "categorySchemaRepository.hpp"

#include <exception>

namespace armai::infrastructure::repositories {

// std::optional<UserRepository::UserDomain> UserRepository::getUserById(const int) const {
//     throw std::exception();
// }

int CategorySchemaRepository::createSchema(const CategorySchemaCreateCommand&) const {
    throw std::exception();
}

} // namespace armai::infrastructure::repositories
