#pragma once

#include <string>

namespace armai::domain::categorySchemas {

struct CategorySchema {
    int id;
    int ownerId;
    std::string name;
    std::string schema;
};

} // namespace armai::domain::categorySchemas
