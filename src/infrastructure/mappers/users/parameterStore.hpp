#pragma once

#include <userver/storages/postgres/parameter_store.hpp>

#include <application/dto/users/userRegisterCommand.hpp>

namespace armai::infrastructure::mappers::users::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::users::UserRegisterCommand&);

} // namespace armai::infrastructure::mappers::users::parameterStore
