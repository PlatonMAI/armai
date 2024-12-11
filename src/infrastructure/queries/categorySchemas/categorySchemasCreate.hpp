#pragma once

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries::categorySchemas {

const userver::storages::postgres::Query kCreateCategorySchema{
    "INSERT INTO category_schemas(name, owner_id) "
    "VALUES($1, $2)"
    "RETURNING id",
    userver::storages::postgres::Query::Name{"create_category_schema"}
};

} // namespace armai::infrastructure::queries::categorySchemas
