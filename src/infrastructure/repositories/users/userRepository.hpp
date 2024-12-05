#pragma once

#include <optional>

#include <application/dto/users/userRegisterCommand.hpp>
#include <domain/users/user.hpp>

namespace armai::infrastructure::repositories {

class UserRepository {
public:
    using UserDomain = domain::users::User;
    using UserRegisterCommand = application::dto::users::UserRegisterCommand;

    virtual std::optional<UserDomain> getUserByEmail(const std::string&) const;
    virtual std::optional<UserDomain> getUserById(const int) const;

    virtual int createUser(const UserRegisterCommand&) const;
};

} // namespace armai::infrastructure::repositories
