#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::teams {

const userver::storages::postgres::Query kCreateTeam{
    "INSERT INTO teams(name, owner_id) "
    "VALUES($1, $2)"
    "RETURNING id",
    userver::storages::postgres::Query::Name{"create_team"}
};

} // namespace armai::infrastructure::queries::teams
