#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/competitions/competitionMulQuery.hpp>
#include <application/dto/competitions/competitionQuery.hpp>
#include <domain/competitions/competition.hpp>

namespace armai::application::mappers::competitions::dto {

using CompetitionDomain = domain::competitions::Competition;
using CompetitionMulQuery = application::dto::competitions::CompetitionMulQuery;
using CompetitionQuery = application::dto::competitions::CompetitionQuery;

CompetitionMulQuery mulQueryFromDomain(const CompetitionDomain&);
CompetitionQuery queryFromDomain(const CompetitionDomain&);

} // namespace armai::application::mappers::competitions::dto
