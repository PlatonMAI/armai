#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::competitions {

const userver::storages::postgres::Query kCreateCompetition{
    "INSERT INTO competitions(name, hand, category_schema_id, owner_id) "
    "VALUES($1, $2::hand_enum, $3, $4)"
    "RETURNING id",
    userver::storages::postgres::Query::Name{"create_competition"}
};

} // namespace armai::infrastructure::queries::competitions
