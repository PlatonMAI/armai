#include "request.hpp"

#include <userver/formats/parse/common_containers.hpp>

#include <optional>

namespace armai::application::mappers::competitions::request {

CompetitionCreateCommand getCompetitionCreateCommand(const userver::formats::json::Value& body) {
    return CompetitionCreateCommand{
        body["name"].As<std::string>(),
        body["hand"].As<std::optional<std::string>>(),
        body["categorySchemaId"].As<int>()
    };
}

} // namespace armai::application::mappers::competitions::request
