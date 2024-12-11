#pragma once

#include <optional>
#include <vector>

#include <domain/categorySchemas/categorySchema.hpp>
#include <application/dto/categorySchemas/categorySchemaCreateCommand.hpp>

namespace armai::infrastructure::repositories {

class CategorySchemaRepository {
public:
    using CategorySchema = domain::categorySchemas::CategorySchema;
    using CategorySchemaCreateCommand = application::dto::categorySchemas::CategorySchemaCreateCommand;

    virtual int createSchema(const CategorySchemaCreateCommand&, const int ownerId) const;

    virtual std::vector<CategorySchema> getSchemas() const;
    virtual std::optional<CategorySchema> getSchema(const int) const;
};

} // namespace armai::infrastructure::repositories
