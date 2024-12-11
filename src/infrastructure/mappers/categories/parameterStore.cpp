#include "parameterStore.hpp"

#include <userver/storages/postgres/io/optional.hpp>

namespace armai::infrastructure::mappers::categories::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::categories::CategoryCreateCommand& category) {
    userver::storages::postgres::ParameterStore parameters;
    parameters.PushBack(category.schemaId);
    parameters.PushBack(domain::users::kStringOptionalFromSex.at(category.sex));
    parameters.PushBack(category.ageMin);
    parameters.PushBack(category.ageMax);
    parameters.PushBack(category.weightMin);
    parameters.PushBack(category.weightMax);

    return parameters;
}

} // namespace armai::infrastructure::mappers::categories::parameterStore
