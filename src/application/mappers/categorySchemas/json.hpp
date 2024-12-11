#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/categorySchemas/categorySchemaMulQuery.hpp>
#include <application/dto/categorySchemas/categorySchemaQuery.hpp>

namespace armai::application::mappers::categorySchemas::json {

using CategorySchemaMulQuery = application::dto::categorySchemas::CategorySchemaMulQuery;
using CategorySchemaQuery = application::dto::categorySchemas::CategorySchemaQuery;

userver::formats::json::Value toJson(const CategorySchemaMulQuery&);
userver::formats::json::Value toJson(const CategorySchemaQuery&);

} // namespace armai::application::mappers::categorySchemas::json
