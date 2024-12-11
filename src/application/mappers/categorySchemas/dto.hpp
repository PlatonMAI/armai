#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/categorySchemas/categorySchemaMulQuery.hpp>
#include <application/dto/categorySchemas/categorySchemaQuery.hpp>
#include <domain/categorySchemas/categorySchema.hpp>

namespace armai::application::mappers::categorySchemas::dto {

using CategorySchemaDomain = domain::categorySchemas::CategorySchema;
using CategorySchemaMulQuery = application::dto::categorySchemas::CategorySchemaMulQuery;
using CategorySchemaQuery = application::dto::categorySchemas::CategorySchemaQuery;

CategorySchemaMulQuery mulQueryFromDomain(const CategorySchemaDomain&);
CategorySchemaQuery queryFromDomain(const CategorySchemaDomain&);

} // namespace armai::application::mappers::categorySchemas::dto
