#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::participants {

const userver::storages::postgres::Query kDeleteUsersUnConfirmed{
    "DELETE FROM participants "
    "WHERE competition_id = $1 AND confirm = false",
    userver::storages::postgres::Query::Name{"delete_users_unconfirmed"}
};

} // namespace armai::infrastructure::queries::participants
