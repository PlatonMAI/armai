#include "appendRepositories.hpp"

#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <infrastructure/components/repositories/categorySchemaRepositoryComponent.hpp>
#include <infrastructure/components/repositories/categoryRepositoryComponent.hpp>
#include <infrastructure/components/repositories/teamRepositoryComponent.hpp>
#include <infrastructure/components/repositories/participantRepositoryComponent.hpp>
#include <infrastructure/components/repositories/competitionRepositoryComponent.hpp>
#include <infrastructure/components/repositories/armfightRepositoryComponent.hpp>

namespace armai::infrastructure::components {

void AppendRepositories(userver::components::ComponentList& component_list) {
    component_list.Append<UserRepositoryComponent>();
    component_list.Append<CategorySchemaRepositoryComponent>();
    component_list.Append<CategoryRepositoryComponent>();
    component_list.Append<TeamRepositoryComponent>();
    component_list.Append<ParticipantRepositoryComponent>();
    component_list.Append<CompetitionRepositoryComponent>();
    component_list.Append<ArmfightRepositoryComponent>();
}

} // namespace armai::infrastructure::repositories
