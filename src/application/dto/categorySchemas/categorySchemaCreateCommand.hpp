#pragma once

#include <string>

namespace armai::application::dto::categorySchemas {

struct CategorySchemaCreateCommand {
    std::string name;
    std::string schema;
};

} // namespace armai::application::dto::categorySchemas
