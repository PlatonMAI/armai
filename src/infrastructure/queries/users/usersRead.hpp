#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::users {

const userver::storages::postgres::Query kSelectUserByEmail{
    "SELECT id, email, password, name, sex, birth, is_admin, wins_armfights, wins_competitions "
    "FROM users "
    "WHERE email = $1",
    userver::storages::postgres::Query::Name{"select_user_by_email"}
};

const userver::storages::postgres::Query kSelectUserById{
    "SELECT id, email, password, name, sex, birth, is_admin, wins_armfights, wins_competitions "
    "FROM users "
    "WHERE id = $1",
    userver::storages::postgres::Query::Name{"select_user_by_id"}
};

} // namespace armai::infrastructure::queries::users
