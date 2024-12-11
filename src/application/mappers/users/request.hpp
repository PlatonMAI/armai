#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/users/userRegisterCommand.hpp>
#include <application/dto/users/userAuthCommand.hpp>

namespace armai::application::mappers::users::request {

using UserRegisterCommand = application::dto::users::UserRegisterCommand;
using UserAuthCommand = application::dto::users::UserAuthCommand;

UserRegisterCommand getUserRegisterCommand(const userver::formats::json::Value&);
UserAuthCommand getUserAuthCommand(const userver::formats::json::Value&);

} // namespace armai::application::mappers::users::request
