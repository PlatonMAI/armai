#include "competitionRepositoryPostgres.hpp"

#include <optional>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/parameter_store.hpp>
#include <userver/storages/postgres/io/date.hpp>

#include <infrastructure/queries/competitions/competitionsCreate.hpp>
#include <infrastructure/queries/competitions/competitionsRead.hpp>
#include <infrastructure/queries/competitions/competitionsUpdate.hpp>
#include <infrastructure/mappers/competitions/parameterStore.hpp>
#include <infrastructure/mappers/postgres/hand.hpp>
#include <infrastructure/mappers/postgres/status.hpp>

namespace armai::infrastructure::repositories::competitions {

int CompetitionRepositoryPostgres::createCompetition(const CompetitionCreateCommand& competition, const int ownerId) const {
    auto parameterStore = mappers::competitions::parameterStore::toStore(competition);
    parameterStore.PushBack(ownerId);
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::competitions::kCreateCompetition, parameterStore);

    return res.AsSingleRow<int>();
}

std::vector<CompetitionRepositoryPostgres::Competition> CompetitionRepositoryPostgres::getCompetitions() const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::competitions::kSelectAllCompetitions);

    return res.AsContainer<std::vector<Competition>>(userver::storages::postgres::kRowTag);
}
std::vector<CompetitionRepositoryPostgres::Competition> CompetitionRepositoryPostgres::getCompetitionsByStatus(const Status status) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::competitions::kSelectCompetitionsByStatus, status);

    return res.AsContainer<std::vector<Competition>>(userver::storages::postgres::kRowTag);
}
std::optional<CompetitionRepositoryPostgres::Competition> CompetitionRepositoryPostgres::getCompetition(const int id) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::competitions::kSelectCompetitionById, id);
    if (res.IsEmpty()) {
        return {};
    }

    return res.AsOptionalSingleRow<Competition>(userver::storages::postgres::kRowTag);
}

bool CompetitionRepositoryPostgres::changeStatus(const int id, const Status status) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::competitions::kChangeStatus, id, status);

    return res.AsOptionalSingleRow<int>().has_value();
}

} // namespace armai::infrastructure::repositories::competitions
