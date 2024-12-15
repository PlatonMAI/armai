#include "teamRepositoryPostgres.hpp"

#include <optional>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/parameter_store.hpp>
#include <userver/storages/postgres/io/date.hpp>

#include <infrastructure/queries/teams/teamsCreate.hpp>
#include <infrastructure/queries/teams/teamsRead.hpp>
#include <infrastructure/mappers/teams/parameterStore.hpp>

namespace armai::infrastructure::repositories::teams {

int TeamRepositoryPostgres::createTeam(const TeamCreateCommand& team, const int ownerId) const {
    auto parameterStore = mappers::teams::parameterStore::toStore(team);
    parameterStore.PushBack(ownerId);
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::teams::kCreateTeam, parameterStore);

    return res.AsSingleRow<int>();
}

std::vector<TeamRepositoryPostgres::Team> TeamRepositoryPostgres::getTeams() const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::teams::kSelectAllTeams);

    return res.AsContainer<std::vector<Team>>(userver::storages::postgres::kRowTag);
}
std::optional<TeamRepositoryPostgres::Team> TeamRepositoryPostgres::getTeam(const int id) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::teams::kSelectTeamById, id);
    if (res.IsEmpty()) {
        return {};
    }

    return res.AsOptionalSingleRow<Team>(userver::storages::postgres::kRowTag);
}

} // namespace armai::infrastructure::repositories::teams
