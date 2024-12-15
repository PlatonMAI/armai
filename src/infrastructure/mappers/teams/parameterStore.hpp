#pragma once

#include <userver/storages/postgres/parameter_store.hpp>

#include <application/dto/teams/teamCreateCommand.hpp>

namespace armai::infrastructure::mappers::teams::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::teams::TeamCreateCommand&);

} // namespace armai::infrastructure::mappers::teams::parameterStore
