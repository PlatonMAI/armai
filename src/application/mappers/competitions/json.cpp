#include "json.hpp"

#include <userver/formats/json/inline.hpp>
#include <userver/formats/serialize/common_containers.hpp>
#include <userver/formats/json/value_builder.hpp>

#include <domain/competitions/competitions.hpp>

namespace armai::application::mappers::competitions::json {

userver::formats::json::Value toJson(const CompetitionMulQuery& competition) {
    return userver::formats::json::MakeObject(
        "id", competition.id,
        "name", competition.name,
        "status", domain::competitions::kStringFromStatus.at(competition.status)
    );
}

userver::formats::json::Value toJson(const CompetitionQuery& competition) {
    userver::formats::json::ValueBuilder competitionJson;
    competitionJson["id"] = competition.id;
    competitionJson["name"] = competition.name;
    competitionJson["hand"] = domain::competitions::kStringOptionalFromHand.at(competition.hand);
    competitionJson["status"] = domain::competitions::kStringFromStatus.at(competition.status);
    competitionJson["isOwner"] = competition.isOwner;
    
    return competitionJson.ExtractValue();
}

userver::formats::json::Value toJson(const ParticipantAsUser& user) {
    userver::formats::json::ValueBuilder userJson;
    userJson["participantId"] = user.participantId;
    userJson["userId"] = user.userId;
    userJson["name"] = user.name;
    userJson["teamId"] = user.teamId;
    userJson["teamName"] = user.teamName;
    userJson["weight"] = user.weight;
    
    return userJson.ExtractValue();
}

} // namespace armai::application::mappers::competitions::json
