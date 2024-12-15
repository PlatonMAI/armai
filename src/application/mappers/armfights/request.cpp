#include "request.hpp"

namespace armai::application::mappers::armfights::request {

ArmfightWinCommand getArmfightWinCommand(const userver::formats::json::Value& body) {
    return ArmfightWinCommand{
        body["id"].As<int>(),
        body["winnerId"].As<int>()
    };
}

} // namespace armai::application::mappers::armfights::request
