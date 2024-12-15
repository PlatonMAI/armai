#include "parameterStore.hpp"

namespace armai::infrastructure::mappers::teams::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::teams::TeamCreateCommand& team) {
    userver::storages::postgres::ParameterStore parameters;
    parameters.PushBack(team.name);

    return parameters;
}

} // namespace armai::infrastructure::mappers::teams::parameterStore
