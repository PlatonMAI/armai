#include "categorySchemaRepositoryPostgres.hpp"

#include <optional>
#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/parameter_store.hpp>
#include <userver/storages/postgres/io/date.hpp>

#include <infrastructure/queries/categorySchemas/categorySchemasCreate.hpp>
#include <infrastructure/queries/categorySchemas/categorySchemasRead.hpp>
#include <infrastructure/mappers/categorySchemas/parameterStore.hpp>

namespace armai::infrastructure::repositories::categorySchemas {

int CategorySchemaRepositoryPostgres::createSchema(const CategorySchemaCreateCommand& categorySchema, const int ownerId) const {
    auto parameterStore = mappers::categorySchemas::parameterStore::toStore(categorySchema);
    parameterStore.PushBack(ownerId);
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::categorySchemas::kCreateCategorySchema, parameterStore);

    return res.AsSingleRow<int>();
}

std::vector<CategorySchemaRepositoryPostgres::CategorySchema> CategorySchemaRepositoryPostgres::getSchemas() const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::categorySchemas::kSelectAllSchemas);

    return res.AsContainer<std::vector<CategorySchema>>(userver::storages::postgres::kRowTag);
}
std::optional<CategorySchemaRepositoryPostgres::CategorySchema> CategorySchemaRepositoryPostgres::getSchema(const int id) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::categorySchemas::kSelectSchemaById, id);
    if (res.IsEmpty()) {
        return {};
    }

    return res.AsOptionalSingleRow<CategorySchema>(userver::storages::postgres::kRowTag);
}

} // namespace armai::infrastructure::repositories::categorySchemas
