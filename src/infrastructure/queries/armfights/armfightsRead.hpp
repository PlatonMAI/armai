#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::armfights {

const userver::storages::postgres::Query kGetArmfight{
    "SELECT "
        "id, "
        "competition_id, "
        "category_id, "
        "participant_first_id, "
        "participant_second_id, "
        "armfight_first_id, "
        "armfight_second_id, "
        "hand, "
        "winner_id "
    "FROM armfights "
    "WHERE "
        "competition_id = $1 AND "
        "category_id = $2 AND "
        "participant_first_id IS NOT NULL AND participant_second_id IS NOT NULL AND "
        "winner_id IS NULL "
    "LIMIT 1",
    userver::storages::postgres::Query::Name{"get_armfight"}
};

} // namespace armai::infrastructure::queries::armfights
