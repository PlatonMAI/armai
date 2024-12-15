#include "request.hpp"

namespace armai::application::mappers::teams::request {

TeamCreateCommand getTeamCreateCommand(const userver::formats::json::Value& body) {
    return TeamCreateCommand{
        body["name"].As<std::string>()
    };
}

} // namespace armai::application::mappers::teams::request
