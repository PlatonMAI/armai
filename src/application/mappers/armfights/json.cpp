#include "json.hpp"

#include <userver/formats/json/inline.hpp>
#include <userver/formats/json/value_builder.hpp>

#include <domain/competitions/competitions.hpp>

namespace armai::application::mappers::armfights::json {

userver::formats::json::Value toJson(const ArmfightQuery& armfight) {
    userver::formats::json::ValueBuilder armfightJson;
    armfightJson["id"] = armfight.id;
    armfightJson["participantFirstId"] = armfight.participantFirstId;
    armfightJson["participantSecondId"] = armfight.participantSecondId;
    armfightJson["hand"] = domain::competitions::kStringFromHand.at(armfight.hand);
    armfightJson["participantFirstName"] = armfight.participantFirstName;
    armfightJson["participantSecondName"] = armfight.participantSecondName;
    
    return armfightJson.ExtractValue();
}

} // namespace armai::application::mappers::armfights::json
