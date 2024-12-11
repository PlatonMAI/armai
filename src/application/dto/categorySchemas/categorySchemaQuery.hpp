#pragma once

#include <string>
#include <vector>

#include <application/dto/categories/categoryQuery.hpp>
#include <domain/users/users.hpp>

namespace armai::application::dto::categorySchemas {

struct CategorySchemaQuery {
    int id;
    std::string name;
    std::vector<categories::CategoryQuery> categories;
};

} // namespace armai::application::dto::categorySchemas
