#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::participants {

const userver::storages::postgres::Query kConfirmationParticipant{
    "UPDATE participants "
    "SET confirm = true "
    "WHERE competition_id = $1 AND user_id = $2 "
    "RETURNING id",
    userver::storages::postgres::Query::Name{"confirmation_participant"}
};

const userver::storages::postgres::Query kWeighingParticipant{
    "UPDATE participants "
    "SET weight = $2 "
    "WHERE id = $1 "
    "RETURNING id",
    userver::storages::postgres::Query::Name{"weighing_participant"}
};

const userver::storages::postgres::Query kSetCategory{
    "UPDATE participants "
    "SET category_id = $2 "
    "WHERE id = $1 "
    "RETURNING id",
    userver::storages::postgres::Query::Name{"set_category"}
};

} // namespace armai::infrastructure::queries::participants
