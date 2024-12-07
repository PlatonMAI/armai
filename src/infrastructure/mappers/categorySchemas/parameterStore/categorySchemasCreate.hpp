#pragma once

#include <userver/storages/postgres/parameter_store.hpp>

#include <application/dto/categorySchemas/categorySchemaCreateCommand.hpp>

namespace armai::infrastructure::mappers::categorySchemas::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::categorySchemas::CategorySchemaCreateCommand&);

} // namespace armai::infrastructure::mappers::categorySchemas::parameterStore
