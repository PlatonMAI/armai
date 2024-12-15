#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::competitions {

const userver::storages::postgres::Query kSelectAllCompetitions{
    "SELECT id, owner_id, name, hand, category_schema_id, status "
    "FROM competitions",
    userver::storages::postgres::Query::Name{"select_all_competitions"}
};
const userver::storages::postgres::Query kSelectCompetitionsByStatus{
    "SELECT id, owner_id, name, hand, category_schema_id, status "
    "FROM competitions "
    "WHERE status = $1::status_enum",
    userver::storages::postgres::Query::Name{"select_competitions_by_status"}
};
const userver::storages::postgres::Query kSelectCompetitionById{
    "SELECT id, owner_id, name, hand, category_schema_id, status "
    "FROM competitions "
    "WHERE id = $1",
    userver::storages::postgres::Query::Name{"select_competition_by_id"}
};

} // namespace armai::infrastructure::queries::competitions
