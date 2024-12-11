#pragma once

#include <application/dto/users/userQuery.hpp>
#include <domain/users/user.hpp>

namespace armai::application::mappers::users::dto {

using UserDomain = domain::users::User;
using UserQuery = application::dto::users::UserQuery;

UserQuery queryFromDomain(const UserDomain&);

} // namespace armai::application::mappers::users::dto
