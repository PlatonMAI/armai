#include "parameterStore.hpp"

namespace armai::infrastructure::mappers::participants::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::participants::ParticipantRegisterCommand& participant) {
    userver::storages::postgres::ParameterStore parameters;
    parameters.PushBack(participant.teamId);

    return parameters;
}
userver::storages::postgres::ParameterStore toStore(const application::dto::participants::ParticipantWeighingCommand& participant) {
    userver::storages::postgres::ParameterStore parameters;
    parameters.PushBack(participant.participantId);
    parameters.PushBack(participant.weight);

    return parameters;
}

} // namespace armai::infrastructure::mappers::participants::parameterStore
