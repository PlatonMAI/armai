#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/categories/categoryCreateCommand.hpp>
#include <application/dto/categories/categoryQuery.hpp>
#include <domain/categories/category.hpp>

namespace armai::application::mappers::categories::dto {

using CategoryDomain = domain::categories::Category;
using CategoryCreateCommand = application::dto::categories::CategoryCreateCommand;
using CategoryQuery = application::dto::categories::CategoryQuery;

CategoryCreateCommand createCommandFromDomain(const CategoryDomain&);
CategoryQuery queryFromDomain(const CategoryDomain&);

} // namespace armai::application::mappers::categories::dto
