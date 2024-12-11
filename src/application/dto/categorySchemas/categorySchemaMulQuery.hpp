#pragma once

#include <string>

#include <domain/users/users.hpp>

namespace armai::application::dto::categorySchemas {

struct CategorySchemaMulQuery {
    int id;
    std::string name;
};

} // namespace armai::application::dto::categorySchemas
