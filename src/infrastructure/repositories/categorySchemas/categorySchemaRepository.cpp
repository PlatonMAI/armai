#include "categorySchemaRepository.hpp"

#include <exception>

namespace armai::infrastructure::repositories {

// std::optional<UserRepository::UserDomain> UserRepository::getUserById(const int) const {
//     throw std::exception();
// }

int CategorySchemaRepository::createSchema(const CategorySchemaCreateCommand&, const int) const {
    throw std::exception();
}

std::vector<CategorySchemaRepository::CategorySchema> CategorySchemaRepository::getSchemas() const {
    throw std::exception();
}

std::optional<CategorySchemaRepository::CategorySchema> CategorySchemaRepository::getSchema(const int) const {
    throw std::exception();
}

} // namespace armai::infrastructure::repositories
