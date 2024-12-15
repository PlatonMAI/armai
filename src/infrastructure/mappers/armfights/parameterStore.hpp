#pragma once

#include <userver/storages/postgres/parameter_store.hpp>

#include <application/dto/armfights/armfightCreateCommand.hpp>
#include <application/dto/armfights/armfightWinCommand.hpp>

namespace armai::infrastructure::mappers::armfights::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::armfights::ArmfightCreateCommand&);
userver::storages::postgres::ParameterStore toStore(const application::dto::armfights::ArmfightWinCommand&);

} // namespace armai::infrastructure::mappers::armfights::parameterStore
