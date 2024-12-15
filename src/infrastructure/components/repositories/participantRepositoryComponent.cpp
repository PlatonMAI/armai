#include "participantRepositoryComponent.hpp"

namespace armai::infrastructure::components {

std::shared_ptr<repositories::ParticipantRepository> ParticipantRepositoryComponent::GetParticipantRepository() const {
    return participant_repository_;
}

} // namespace armai::infrastructure::components
