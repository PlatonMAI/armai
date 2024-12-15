#include "request.hpp"

#include <userver/formats/parse/common_containers.hpp>

#include <optional>

namespace armai::application::mappers::participants::request {

ParticipantRegisterCommand getParticipantRegisterCommand(const userver::formats::json::Value& body) {
    return ParticipantRegisterCommand{
        body["teamId"].As<std::optional<int>>()
    };
}
ParticipantWeighingCommand getParticipantWeighingCommand(const userver::formats::json::Value& body) {
    return ParticipantWeighingCommand{
        body["participantId"].As<int>(),
        body["weight"].As<int>()
    };
}

} // namespace armai::application::mappers::participants::request
