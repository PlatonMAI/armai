#pragma once

#include <string>

#include <userver/utils/datetime/date.hpp>

#include "../../../domain/users/users.hpp"

namespace armai::apllication::dto::users {
    struct UserRegisterCommand {
        std::string email;
        std::string password;
        std::string name;
        domain::users::kSex sex;
        userver::utils::datetime::Date birth;
    };
}
