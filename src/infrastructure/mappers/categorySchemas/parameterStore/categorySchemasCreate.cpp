#include "categorySchemasCreate.hpp"

namespace armai::infrastructure::mappers::categorySchemas::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::categorySchemas::CategorySchemaCreateCommand& categorySchema) {
    userver::storages::postgres::ParameterStore parameters;
    parameters.PushBack(categorySchema.name);
    parameters.PushBack(categorySchema.schema);

    return parameters;
}

} // namespace armai::infrastructure::mappers::categorySchemas::parameterStore
