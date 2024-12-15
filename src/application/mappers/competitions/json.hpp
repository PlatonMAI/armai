#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/competitions/competitionMulQuery.hpp>
#include <application/dto/competitions/competitionQuery.hpp>
#include <domain/participants/participantAsUser.hpp>

namespace armai::application::mappers::competitions::json {

using CompetitionMulQuery = application::dto::competitions::CompetitionMulQuery;
using CompetitionQuery = application::dto::competitions::CompetitionQuery;

userver::formats::json::Value toJson(const CompetitionMulQuery&);
userver::formats::json::Value toJson(const CompetitionQuery&);


using ParticipantAsUser = domain::participants::ParticipantAsUser;

userver::formats::json::Value toJson(const ParticipantAsUser&);

} // namespace armai::application::mappers::competitions::json
