#include "parameterStore.hpp"

namespace armai::infrastructure::mappers::competitions::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::competitions::CompetitionCreateCommand& competition) {
    userver::storages::postgres::ParameterStore parameters;
    parameters.PushBack(competition.name);
    parameters.PushBack(competition.hand);
    parameters.PushBack(competition.categorySchemaId);

    return parameters;
}

} // namespace armai::infrastructure::mappers::competitions::parameterStore
