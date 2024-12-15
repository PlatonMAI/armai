#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::armfights {

const userver::storages::postgres::Query kCreateArmfight{
    "INSERT INTO armfights(competition_id, category_id, participant_first_id, participant_second_id, armfight_first_id, armfight_second_id, hand, is_final) "
    "VALUES($1, $2, $3, $4, $5, $6, $7::hand_enum, $8)"
    "RETURNING id",
    userver::storages::postgres::Query::Name{"create_armfight"}
};

} // namespace armai::infrastructure::queries::armfights
