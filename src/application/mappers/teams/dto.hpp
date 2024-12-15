#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/teams/teamMulQuery.hpp>
#include <application/dto/teams/teamQuery.hpp>
#include <domain/teams/team.hpp>

namespace armai::application::mappers::teams::dto {

using TeamDomain = domain::teams::Team;
using TeamMulQuery = application::dto::teams::TeamMulQuery;
using TeamQuery = application::dto::teams::TeamQuery;

TeamMulQuery mulQueryFromDomain(const TeamDomain&);
TeamQuery queryFromDomain(const TeamDomain&);

} // namespace armai::application::mappers::teams::dto
