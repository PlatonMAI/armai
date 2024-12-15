#include "armfightRepositoryPostgres.hpp"

#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/parameter_store.hpp>
#include <userver/storages/postgres/io/date.hpp>

#include <infrastructure/mappers/armfights/parameterStore.hpp>
#include <infrastructure/mappers/postgres/hand.hpp>
#include <infrastructure/queries/armfights/armfightsCreate.hpp>
#include <infrastructure/queries/armfights/armfightsRead.hpp>
#include <infrastructure/queries/armfights/armfightsUpdate.hpp>

namespace armai::infrastructure::repositories::armfights {

int ArmfightRepositoryPostgres::createArmfight(const ArmfightCreateCommand& armfight) const {
    const auto parameterStore = mappers::armfights::parameterStore::toStore(armfight);
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::armfights::kCreateArmfight, parameterStore);

    return res.AsSingleRow<int>();
}

bool ArmfightRepositoryPostgres::winArmfight(const ArmfightWinCommand& armfight) const {
    const auto parameterStore = mappers::armfights::parameterStore::toStore(armfight);
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::armfights::kWinArmfight, parameterStore);

    return res.AsOptionalSingleRow<int>().has_value();
}

std::optional<ArmfightRepositoryPostgres::Armfight> ArmfightRepositoryPostgres::getArmfight(const int competitionId, const int categoryId) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::armfights::kGetArmfight, competitionId, categoryId);

    return res.AsOptionalSingleRow<Armfight>(userver::v2_2_rc::storages::postgres::kRowTag);
}

} // namespace armai::infrastructure::repositories::armfights
