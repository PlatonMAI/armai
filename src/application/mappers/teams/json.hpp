#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/teams/teamMulQuery.hpp>
#include <application/dto/teams/teamQuery.hpp>
#include <domain/teams/participant.hpp>

namespace armai::application::mappers::teams::json {

using TeamMulQuery = application::dto::teams::TeamMulQuery;
using TeamQuery = application::dto::teams::TeamQuery;
using Participant = domain::teams::Participant;

userver::formats::json::Value toJson(const Participant&);
userver::formats::json::Value toJson(const TeamMulQuery&);
userver::formats::json::Value toJson(const TeamQuery&);

} // namespace armai::application::mappers::teams::json
