#pragma once

#include <userver/storages/postgres/cluster.hpp>

#include <infrastructure/repositories/armfights/armfightRepository.hpp>

namespace armai::infrastructure::repositories::armfights {

class ArmfightRepositoryPostgres : public ArmfightRepository {
public:
    ArmfightRepositoryPostgres(const userver::storages::postgres::ClusterPtr pg_cluster) : pg_cluster_(pg_cluster) {}

    virtual int createArmfight(const ArmfightCreateCommand&) const override final;

    virtual bool winArmfight(const ArmfightWinCommand&) const override final;

    virtual std::optional<Armfight> getArmfight(const int competitionId, const int categoryId) const override final;

private:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace armai::infrastructure::repositories::armfights
