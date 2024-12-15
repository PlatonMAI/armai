#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::participants {

const userver::storages::postgres::Query kCheckRegisterParticipant{
    "SELECT id "
    "FROM participants "
    "WHERE competition_id = $1 AND user_id = $2",
    userver::storages::postgres::Query::Name{"select_check_register_participant"}
};
const userver::storages::postgres::Query kCheckConfirmationParticipant{
    "SELECT id "
    "FROM participants "
    "WHERE competition_id = $1 AND user_id = $2 AND confirm = true",
    userver::storages::postgres::Query::Name{"select_check_confirmation_participant"}
};

const userver::storages::postgres::Query kSelectUsersRegisteredCompetition{
    "SELECT participants.id, users.id, users.name, teams.id, teams.name, participants.weight, participants.age, users.sex "
    "FROM participants "
    "LEFT JOIN users ON users.id = participants.user_id "
    "LEFT JOIN teams ON teams.id = participants.team_id "
    "WHERE participants.competition_id = $1",
    userver::storages::postgres::Query::Name{"select_users_registered_competition"}
};
const userver::storages::postgres::Query kSelectUsersConfirmedCompetition{
    "SELECT participants.id, users.id, users.name, teams.id, teams.name, participants.weight, participants.age, users.sex "
    "FROM participants "
    "LEFT JOIN users ON users.id = participants.user_id "
    "LEFT JOIN teams ON teams.id = participants.team_id "
    "WHERE participants.competition_id = $1 AND participants.confirm = true",
    userver::storages::postgres::Query::Name{"select_users_registered_competition"}
};

const userver::storages::postgres::Query kSelectParticipantsNotWeighing{
    "SELECT id "
    "FROM participants "
    "WHERE competition_id = $1 AND weight is null",
    userver::storages::postgres::Query::Name{"select_participants_not_weighing"}
};

const userver::storages::postgres::Query kSelectParticipantsByTeam{
    "SELECT DISTINCT user_id "
    "FROM participants "
    "WHERE team_id = $1",
    userver::storages::postgres::Query::Name{"select_participants_by_team"}
};
const userver::storages::postgres::Query kSelectParticipantById{
    "SELECT id, user_id, competition_id, team_id, weight, age "
    "FROM participants "
    "WHERE id = $1",
    userver::storages::postgres::Query::Name{"select_participant_by_id"}
};

const userver::storages::postgres::Query kSelectWinnerCategoryCompetition{
    "SELECT armfights.winner_id, users.id, users.name, teams.id, teams.name, participants.weight, participants.age, users.sex "
    "FROM armfights "
    "LEFT join participants on participants.id = armfights.winner_id "
    "LEFT JOIN users ON users.id = participants.user_id "
    "LEFT JOIN teams ON teams.id = participants.team_id "
    "where "
        "armfights.competition_id = $1 and "
        "armfights.category_id = $2 and "
        "armfights.is_final = true",
    userver::storages::postgres::Query::Name{"select_winner_category_competition"}
};

} // namespace armai::infrastructure::queries::participants
