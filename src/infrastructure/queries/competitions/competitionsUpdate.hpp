#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::competitions {

const userver::storages::postgres::Query kChangeStatus{
    "UPDATE competitions "
    "SET status = $2 "
    "WHERE id = $1 "
    "RETURNING id",
    userver::storages::postgres::Query::Name{"create_competition"}
};

} // namespace armai::infrastructure::queries::competitions
