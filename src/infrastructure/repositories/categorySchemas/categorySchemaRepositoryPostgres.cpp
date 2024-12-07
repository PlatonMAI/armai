#include "categorySchemaRepositoryPostgres.hpp"

#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/parameter_store.hpp>
#include <userver/storages/postgres/io/date.hpp>

#include <infrastructure/queries/users/usersRead.hpp>
#include <infrastructure/queries/users/usersCreate.hpp>
#include <infrastructure/mappers/categorySchemas/parameterStore/categorySchemasCreate.hpp>

namespace armai::infrastructure::repositories::categorySchemas {

// std::optional<UserRepositoryPostgres::UserDomain> UserRepositoryPostgres::getUserById(const int id) const {
//     const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::users::kSelectUserById, id);
//     if (res.IsEmpty()) {
//         return {};
//     }

//     return res.AsOptionalSingleRow<UserDomain>(userver::storages::postgres::kRowTag);
// }

int CategorySchemaRepositoryPostgres::createSchema(const CategorySchemaCreateCommand& categorySchema) const {
    const auto parameterStore = mappers::categorySchemas::parameterStore::toStore(categorySchema);
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::users::kCreateuser, parameterStore);

    return res.AsSingleRow<int>();
}

} // namespace armai::infrastructure::repositories::categorySchemas
