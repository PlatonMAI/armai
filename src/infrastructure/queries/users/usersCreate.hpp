#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::users {

const userver::storages::postgres::Query kCreateUser{
    "INSERT INTO users(email, password, name, sex, birth) "
    "VALUES($1, $2, $3, $4::sex_enum, $5::date)"
    "RETURNING id",
    userver::storages::postgres::Query::Name{"create_user"}
};

} // namespace armai::infrastructure::queries::users
