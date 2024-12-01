#pragma once

#include <userver/formats/json/value.hpp>

#include "../../dto/users/userRegisterCommand.hpp"

namespace armai::application::mappers::users {
    using UserRegisterCommand = apllication::dto::users::UserRegisterCommand;
    UserRegisterCommand getUserRegisterCommand(const userver::formats::json::Value&);
}
