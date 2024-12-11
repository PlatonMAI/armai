#include "categoryRepositoryPostgres.hpp"

#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/parameter_store.hpp>

#include <infrastructure/queries/categories/categoriesCreate.hpp>
#include <infrastructure/queries/categories/categoriesRead.hpp>
#include <infrastructure/mappers/categories/parameterStore.hpp>
#include <infrastructure/mappers/postgres/sex.hpp>

namespace armai::infrastructure::repositories::categories {

int CategoryRepositoryPostgres::createCategory(const CategoryCreateCommand& category) const {
    const auto parameterStore = mappers::categories::parameterStore::toStore(category);
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::categories::kCreateCategory, parameterStore);

    return res.AsSingleRow<int>();
}

std::vector<CategoryRepositoryPostgres::Category> CategoryRepositoryPostgres::getCategories(const int schemaId) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::categories::kSelectAllCategoriesBySchemaId, schemaId);

    return res.AsContainer<std::vector<Category>>(userver::storages::postgres::kRowTag);
}

} // namespace armai::infrastructure::repositories::categories
