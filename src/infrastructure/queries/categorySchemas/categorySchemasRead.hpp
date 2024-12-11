#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::categorySchemas {

const userver::storages::postgres::Query kSelectAllSchemas{
    "SELECT id, owner_id, name "
    "FROM category_schemas",
    userver::storages::postgres::Query::Name{"select_all_category_schemas"}
};
const userver::storages::postgres::Query kSelectSchemaById{
    "SELECT id, owner_id, name "
    "FROM category_schemas "
    "WHERE id = $1",
    userver::storages::postgres::Query::Name{"select_category_schema_by_id"}
};

} // namespace armai::infrastructure::queries::categorySchemas
