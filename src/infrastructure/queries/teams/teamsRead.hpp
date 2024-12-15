#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::teams {

const userver::storages::postgres::Query kSelectAllTeams{
    "SELECT id, owner_id, name, wins_armfights, wins_competitions "
    "FROM teams",
    userver::storages::postgres::Query::Name{"select_all_teams"}
};
const userver::storages::postgres::Query kSelectTeamById{
    "SELECT id, owner_id, name, wins_armfights, wins_competitions "
    "FROM teams "
    "WHERE id = $1",
    userver::storages::postgres::Query::Name{"select_team_by_id"}
};

} // namespace armai::infrastructure::queries::teams
