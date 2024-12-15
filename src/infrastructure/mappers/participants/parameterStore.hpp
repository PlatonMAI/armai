#pragma once

#include <userver/storages/postgres/parameter_store.hpp>

#include <application/dto/participants/participantRegisterCommand.hpp>
#include <application/dto/participants/participantWeighingCommand.hpp>

namespace armai::infrastructure::mappers::participants::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::participants::ParticipantRegisterCommand&);
userver::storages::postgres::ParameterStore toStore(const application::dto::participants::ParticipantWeighingCommand&);

} // namespace armai::infrastructure::mappers::participants::parameterStore
