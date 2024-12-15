#include "competitionRepositoryComponent.hpp"

namespace armai::infrastructure::components {

std::shared_ptr<repositories::CompetitionRepository> CompetitionRepositoryComponent::GetCompetitionRepository() const {
    return competition_repository_;
}

} // namespace armai::infrastructure::components
