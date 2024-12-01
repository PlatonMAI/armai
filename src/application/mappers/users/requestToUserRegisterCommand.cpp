#include "requestToUserRegisterCommand.hpp"

#include "../../../domain/domain.hpp"

namespace armai::application::mappers::users {
    UserRegisterCommand getUserRegisterCommand(const userver::formats::json::Value &body) {
        return UserRegisterCommand{
            body["email"].As<std::string>(),
            body["password"].As<std::string>(),
            body["name"].As<std::string>(),
            domain::users::kSexFromString.at(body["sex"].As<std::string>()),
            domain::getDateFromString(body["birth"].As<std::string>())
        };
    }
}
