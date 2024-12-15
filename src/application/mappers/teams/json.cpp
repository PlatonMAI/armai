#include "json.hpp"

#include <userver/formats/json/inline.hpp>
#include <userver/formats/json/value_builder.hpp>

namespace armai::application::mappers::teams::json {

userver::formats::json::Value toJson(const Participant& participant) {
    return userver::formats::json::MakeObject(
        "id", participant.id,
        "name", participant.name
    );
}

userver::formats::json::Value toJson(const TeamMulQuery& team) {
    return userver::formats::json::MakeObject(
        "id", team.id,
        "name", team.name
    );
}

userver::formats::json::Value toJson(const TeamQuery& team) {
    userver::formats::json::ValueBuilder teamJson;
    teamJson["id"] = team.id;
    teamJson["name"] = team.name;
    teamJson["winsArmfights"] = team.winsArmfights;
    teamJson["winsCompetitions"] = team.winsCompetitions;

    teamJson["participants"] = userver::formats::json::ValueBuilder{};
    for (const auto& participant : team.participants) {
        teamJson["participants"].PushBack(toJson(participant));
    }
    
    return teamJson.ExtractValue();
}

} // namespace armai::application::mappers::teams::json
