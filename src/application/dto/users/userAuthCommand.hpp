#pragma once

#include <string>

namespace armai::application::dto::users {

struct UserAuthCommand {
    std::string email;
    std::string password;
};

} // namespace armai::application::dto::users
