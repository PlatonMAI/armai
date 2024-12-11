#include "request.hpp"

namespace armai::application::mappers::users::request {

UserRegisterCommand getUserRegisterCommand(const userver::formats::json::Value &body) {
    return UserRegisterCommand{
        body["email"].As<std::string>(),
        body["password"].As<std::string>(),
        body["name"].As<std::string>(),
        body["sex"].As<std::string>(),
        userver::utils::datetime::DateFromRFC3339String(body["birth"].As<std::string>())
    };
}

UserAuthCommand getUserAuthCommand(const userver::formats::json::Value &body) {
    return UserAuthCommand{
        body["email"].As<std::string>(),
        body["password"].As<std::string>()
    };
}

} // namespace armai::application::mappers::users::request
