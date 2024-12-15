#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::participants {

const userver::storages::postgres::Query kCreateParticipant{
    "INSERT INTO participants(team_id, competition_id, user_id) "
    "VALUES($1, $2, $3)"
    "RETURNING id",
    userver::storages::postgres::Query::Name{"create_participant"}
};

} // namespace armai::infrastructure::queries::participants
