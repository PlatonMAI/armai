#pragma once

#include <string>

#include <userver/utils/datetime/date.hpp>

#include <domain/users/users.hpp>

namespace armai::application::dto::users {

struct UserQuery {
    int id;
    std::string name;
    domain::users::Sex sex;
    userver::utils::datetime::Date birth;
    bool isAdmin;
    int winsArmfights;
    int winsCompetitions;
};

} // namespace armai::application::dto::users
