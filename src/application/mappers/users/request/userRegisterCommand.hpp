#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/users/userRegisterCommand.hpp>

namespace armai::application::mappers::users::request {

using UserRegisterCommand = application::dto::users::UserRegisterCommand;
UserRegisterCommand getUserRegisterCommand(const userver::formats::json::Value&);

} // namespace armai::application::mappers::users::request
