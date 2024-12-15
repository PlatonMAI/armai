#pragma once

#include <userver/storages/postgres/cluster.hpp>

#include <infrastructure/repositories/competitions/competitionRepository.hpp>

namespace armai::infrastructure::repositories::competitions {

class CompetitionRepositoryPostgres : public CompetitionRepository {
public:
    CompetitionRepositoryPostgres(const userver::storages::postgres::ClusterPtr pg_cluster) : pg_cluster_(pg_cluster) {}

    virtual int createCompetition(const CompetitionCreateCommand&, const int ownerId) const override final;

    virtual std::vector<Competition> getCompetitions() const override final;
    virtual std::vector<Competition> getCompetitionsByStatus(const Status) const override final;
    virtual std::optional<Competition> getCompetition(const int) const override final;

    virtual bool changeStatus(const int, const Status) const override final;

private:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace armai::infrastructure::repositories::competitions
