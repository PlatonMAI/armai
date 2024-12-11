#pragma once

#include <userver/formats/json/value.hpp>

#include <domain/users/user.hpp>
#include <application/dto/users/userQuery.hpp>

namespace armai::application::mappers::users::json {

using UserDomain = domain::users::User;
using UserQuery = application::dto::users::UserQuery;

userver::formats::json::Value toJson(const UserDomain&);
userver::formats::json::Value toJson(const UserQuery&);

} // namespace armai::application::mappers::users::json
