#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/armfights/armfightQuery.hpp>

namespace armai::application::mappers::armfights::json {

using ArmfightQuery = application::dto::armfights::ArmfightQuery;

userver::formats::json::Value toJson(const ArmfightQuery&);

} // namespace armai::application::mappers::armfights::json
