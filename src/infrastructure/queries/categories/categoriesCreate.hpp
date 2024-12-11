#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::categories {

const userver::storages::postgres::Query kCreateCategory{
    "INSERT INTO categories(category_schema_id, sex, age_min, age_max, weight_min, weight_max) "
    "VALUES($1, $2::sex_enum, $3, $4, $5, $6)"
    "RETURNING id",
    userver::storages::postgres::Query::Name{"create_category"}
};

} // namespace armai::infrastructure::queries::categories
