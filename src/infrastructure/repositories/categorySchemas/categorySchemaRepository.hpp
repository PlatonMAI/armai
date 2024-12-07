#pragma once

#include <optional>

#include <domain/categorySchemas/categorySchema.hpp>
#include <application/dto/categorySchemas/categorySchemaCreateCommand.hpp>

namespace armai::infrastructure::repositories {

class CategorySchemaRepository {
public:
    using CategorySchema = domain::categorySchemas::CategorySchema;
    using CategorySchemaCreateCommand = application::dto::categorySchemas::CategorySchemaCreateCommand;

    // virtual std::optional<UserDomain> getUserById(const int) const;

    virtual int createSchema(const CategorySchemaCreateCommand&) const;
};

} // namespace armai::infrastructure::repositories
