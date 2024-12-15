#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/armfights/armfightQuery.hpp>
#include <domain/armfights/armfight.hpp>

namespace armai::application::mappers::armfights::dto {

using ArmfightDomain = domain::armfights::Armfight;
using ArmfightQuery = application::dto::armfights::ArmfightQuery;

ArmfightQuery queryFromDomain(const ArmfightDomain&);

} // namespace armai::application::mappers::armfights::dto
