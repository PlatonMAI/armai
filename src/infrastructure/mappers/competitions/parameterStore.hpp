#pragma once

#include <userver/storages/postgres/parameter_store.hpp>

#include <application/dto/competitions/competitionCreateCommand.hpp>

namespace armai::infrastructure::mappers::competitions::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::competitions::CompetitionCreateCommand&);

} // namespace armai::infrastructure::mappers::competitions::parameterStore
