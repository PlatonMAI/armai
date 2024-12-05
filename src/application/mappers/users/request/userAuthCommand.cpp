#include "userAuthCommand.hpp"

namespace armai::application::mappers::users::request {

UserAuthCommand getUserAuthCommand(const userver::formats::json::Value &body) {
    return UserAuthCommand{
        body["email"].As<std::string>(),
        body["password"].As<std::string>()
    };
}

} // namespace armai::application::mappers::users::request
