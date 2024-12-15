#include "teamRepositoryComponent.hpp"

namespace armai::infrastructure::components {

std::shared_ptr<repositories::TeamRepository> TeamRepositoryComponent::GetTeamRepository() const {
    return team_repository_;
}

} // namespace armai::infrastructure::components
