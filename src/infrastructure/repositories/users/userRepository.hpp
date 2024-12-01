#pragma once

#include <optional>

#include <domain/users/user.hpp>

namespace armai::infrastructure::repositories {

class UserRepository {
public:
    using User = domain::users::User;

    virtual std::optional<int> getUserByEmail(const std::string&) const;
};

} // namespace armai::infrastructure::repositories
