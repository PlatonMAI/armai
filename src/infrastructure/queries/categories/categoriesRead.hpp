#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::categories {

const userver::storages::postgres::Query kSelectAllCategoriesBySchemaId{
    "SELECT id, category_schema_id, sex, age_min, age_max, weight_min, weight_max "
    "FROM categories "
    "WHERE category_schema_id = $1",
    userver::storages::postgres::Query::Name{"select_all_categories_by_schema_id"}
};

} // namespace armai::infrastructure::queries::categories
