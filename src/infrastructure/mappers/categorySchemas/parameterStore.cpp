#include "parameterStore.hpp"

namespace armai::infrastructure::mappers::categorySchemas::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::categorySchemas::CategorySchemaCreateCommand& categorySchema) {
    userver::storages::postgres::ParameterStore parameters;
    parameters.PushBack(categorySchema.name);

    return parameters;
}

} // namespace armai::infrastructure::mappers::categorySchemas::parameterStore
