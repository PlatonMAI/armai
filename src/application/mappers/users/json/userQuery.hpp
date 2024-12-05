#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/users/userQuery.hpp>

namespace armai::application::mappers::users::json {

using UserQuery = dto::users::UserQuery;
userver::formats::json::Value toJson(const UserQuery&);

} // namespace armai::application::mappers::users::json
