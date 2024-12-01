#pragma once

#include <userver/utils/datetime/date.hpp>

#include "users.hpp"

namespace armai::domain::users {
    class User {
        uint id;
        std::string name;
        kSex sex;
        userver::utils::datetime::Date birth;
    };
}
