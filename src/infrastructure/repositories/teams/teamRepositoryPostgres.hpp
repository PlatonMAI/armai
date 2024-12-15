#pragma once

#include <userver/storages/postgres/cluster.hpp>

#include <infrastructure/repositories/teams/teamRepository.hpp>

namespace armai::infrastructure::repositories::teams {

class TeamRepositoryPostgres : public TeamRepository {
public:
    TeamRepositoryPostgres(const userver::storages::postgres::ClusterPtr pg_cluster) : pg_cluster_(pg_cluster) {}

    virtual int createTeam(const TeamCreateCommand&, const int ownerId) const override final;

    virtual std::vector<Team> getTeams() const override final;
    virtual std::optional<Team> getTeam(const int) const override final;

private:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace armai::infrastructure::repositories::teams
