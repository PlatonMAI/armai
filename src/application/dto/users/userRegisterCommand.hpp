#pragma once

#include <string>

#include <userver/utils/datetime/date.hpp>

namespace armai::application::dto::users {

struct UserRegisterCommand {
    std::string email;
    std::string password;
    std::string name;
    std::string sex;
    userver::utils::datetime::Date birth;
};

} // namespace armai::application::dto::users
