#pragma once

#include <userver/storages/postgres/parameter_store.hpp>

#include <application/dto/categories/categoryCreateCommand.hpp>

namespace armai::infrastructure::mappers::categories::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::categories::CategoryCreateCommand&);

} // namespace armai::infrastructure::mappers::categories::parameterStore
