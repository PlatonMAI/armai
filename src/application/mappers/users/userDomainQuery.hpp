#pragma once

#include <application/dto/users/userQuery.hpp>
#include <domain/users/user.hpp>

namespace armai::application::mappers::users {

using UserDomain = domain::users::User;
using UserQuery = dto::users::UserQuery;

UserQuery toQuery(const UserDomain&);

} // namespace armai::application::mappers::users
