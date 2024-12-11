#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/categories/categoryQuery.hpp>

namespace armai::application::mappers::categories::json {

using CategoryQuery = application::dto::categories::CategoryQuery;

userver::formats::json::Value toJson(const CategoryQuery&);

} // namespace armai::application::mappers::categories::json
