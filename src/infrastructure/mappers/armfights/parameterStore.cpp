#include "parameterStore.hpp"
#include "application/dto/armfights/armfightCreateCommand.hpp"

namespace armai::infrastructure::mappers::armfights::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::armfights::ArmfightCreateCommand& armfight) {
    userver::storages::postgres::ParameterStore parameters;
    parameters.PushBack(armfight.competitionId);
    parameters.PushBack(armfight.categoryId);
    parameters.PushBack(armfight.participantFirstId);
    parameters.PushBack(armfight.participantSecondId);
    parameters.PushBack(armfight.armfightFirstId);
    parameters.PushBack(armfight.armfightSecondId);
    parameters.PushBack(armfight.hand);
    parameters.PushBack(armfight.isFinal);

    return parameters;
}
userver::storages::postgres::ParameterStore toStore(const application::dto::armfights::ArmfightWinCommand& armfight) {
    userver::storages::postgres::ParameterStore parameters;
    parameters.PushBack(armfight.id);
    parameters.PushBack(armfight.winnerId);

    return parameters;
}

} // namespace armai::infrastructure::mappers::armfights::parameterStore
