#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/users/userAuthCommand.hpp>

namespace armai::application::mappers::users::request {

using UserAuthCommand = application::dto::users::UserAuthCommand;
UserAuthCommand getUserAuthCommand(const userver::formats::json::Value&);

} // namespace armai::application::mappers::users::request
