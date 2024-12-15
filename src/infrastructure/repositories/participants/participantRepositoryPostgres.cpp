#include "participantRepositoryPostgres.hpp"

#include <optional>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/parameter_store.hpp>
#include <userver/storages/postgres/io/date.hpp>

#include <infrastructure/queries/participants/participantsCreate.hpp>
#include <infrastructure/queries/participants/participantsRead.hpp>
#include <infrastructure/queries/participants/participantsUpdate.hpp>
#include <infrastructure/queries/participants/participantsDelete.hpp>
#include <infrastructure/mappers/participants/parameterStore.hpp>
#include <infrastructure/mappers/postgres/sex.hpp>

namespace armai::infrastructure::repositories::participants {

int ParticipantRepositoryPostgres::registerParticipant(const ParticipantRegisterCommand& participant, const int competitionId, const int userId) const {
    auto parameterStore = mappers::participants::parameterStore::toStore(participant);
    parameterStore.PushBack(competitionId);
    parameterStore.PushBack(userId);
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::participants::kCreateParticipant, parameterStore);

    return res.AsSingleRow<int>();
}
int ParticipantRepositoryPostgres::confirmationParticipant(const int competitionId, const int userId) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::participants::kConfirmationParticipant, competitionId, userId);

    return res.AsSingleRow<int>();
}
int ParticipantRepositoryPostgres::weighingParticipant(const ParticipantWeighingCommand& participant) const {
    auto parameterStore = mappers::participants::parameterStore::toStore(participant);

    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::participants::kWeighingParticipant, parameterStore);

    return res.AsSingleRow<int>();
}

bool ParticipantRepositoryPostgres::checkRegisterParticipant(const int competitionId, const int userId) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::participants::kCheckRegisterParticipant, competitionId, userId);

    const auto participantId = res.AsOptionalSingleRow<int>();
    return participantId.has_value();
}
bool ParticipantRepositoryPostgres::checkConfirmationParticipant(const int competitionId, const int userId) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::participants::kCheckConfirmationParticipant, competitionId, userId);

    const auto participantId = res.AsOptionalSingleRow<int>();
    return participantId.has_value();
}

std::vector<ParticipantRepositoryPostgres::ParticipantAsUser> ParticipantRepositoryPostgres::getUsersRegisteredCompetition(const int competitionId) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::participants::kSelectUsersRegisteredCompetition, competitionId);

    return res.AsContainer<std::vector<ParticipantAsUser>>(userver::storages::postgres::kRowTag);
}
std::vector<ParticipantRepositoryPostgres::ParticipantAsUser> ParticipantRepositoryPostgres::getUsersConfirmedCompetition(const int competitionId) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::participants::kSelectUsersConfirmedCompetition, competitionId);

    return res.AsContainer<std::vector<ParticipantAsUser>>(userver::storages::postgres::kRowTag);
}

std::optional<ParticipantRepositoryPostgres::ParticipantAsUser> ParticipantRepositoryPostgres::getWinnerCategory(const int competitionId, const int categoryId) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::participants::kSelectWinnerCategoryCompetition, competitionId, categoryId);

    return res.AsOptionalSingleRow<ParticipantAsUser>(userver::storages::postgres::kRowTag);
}

void ParticipantRepositoryPostgres::deleteUsersUnConfirmed(const int competitionId) const {
    pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::participants::kDeleteUsersUnConfirmed, competitionId);
}

bool ParticipantRepositoryPostgres::checkEveryoneWeighing(const int competitionId) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::participants::kSelectParticipantsNotWeighing, competitionId);

    return (res.IsEmpty());
}

bool ParticipantRepositoryPostgres::setCategory(const int participantId, const int categoryId) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::participants::kSetCategory, participantId, categoryId);

    return (res.AsOptionalSingleRow<int>().has_value());
}

std::vector<int> ParticipantRepositoryPostgres::getParticipantsByTeam(const int teamId) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::participants::kSelectParticipantsByTeam, teamId);

    return res.AsContainer<std::vector<int>>();
}
std::optional<ParticipantRepositoryPostgres::Participant> ParticipantRepositoryPostgres::getParticipant(const int id) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::participants::kSelectParticipantById, id);

    return res.AsOptionalSingleRow<Participant>(userver::storages::postgres::kRowTag);
}

} // namespace armai::infrastructure::repositories::participants
