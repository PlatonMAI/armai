#pragma once

#include <string>

namespace armai::domain::categorySchemas {

struct CategorySchema {
    int id;
    int ownerId;
    std::string name;
};

} // namespace armai::domain::categorySchemas
