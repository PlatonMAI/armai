#pragma once

#include <userver/utils/datetime/date.hpp>

#include "users.hpp"

namespace armai::domain::users {

struct User {
    int id;
    std::string email;
    std::string password;
    std::string name;
    Sex sex;
    userver::utils::datetime::Date birth;
    bool isAdmin;
    int winsArmfights;
    int winsCompetitions;
};

} // namespace armai::domain::users
