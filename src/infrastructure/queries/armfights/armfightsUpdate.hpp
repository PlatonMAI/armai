#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::armfights {

const userver::storages::postgres::Query kWinArmfight{
    "UPDATE armfights "
    "SET winner_id = $2 "
    "WHERE id = $1 "
    "RETURNING id",
    userver::storages::postgres::Query::Name{"win_armfight"}
};

} // namespace armai::infrastructure::queries::armfights
