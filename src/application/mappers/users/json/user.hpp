#pragma once

#include <userver/formats/json/value.hpp>

#include <domain/users/user.hpp>

namespace armai::application::mappers::users::json {

using UserDomain = domain::users::User;
userver::formats::json::Value toJson(const UserDomain&);

} // namespace armai::application::mappers::users::json
