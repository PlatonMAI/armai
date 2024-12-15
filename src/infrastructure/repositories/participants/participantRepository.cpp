#include "participantRepository.hpp"

#include <exception>

namespace armai::infrastructure::repositories {

int ParticipantRepository::registerParticipant(const ParticipantRegisterCommand&, const int, const int) const {
    throw std::exception();
}
int ParticipantRepository::confirmationParticipant(const int, const int) const {
    throw std::exception();
}
int ParticipantRepository::weighingParticipant(const ParticipantWeighingCommand&) const {
    throw std::exception();
}

bool ParticipantRepository::checkRegisterParticipant(const int, const int) const {
    throw std::exception();
}
bool ParticipantRepository::checkConfirmationParticipant(const int, const int) const {
    throw std::exception();
}

std::vector<ParticipantRepository::ParticipantAsUser> ParticipantRepository::getUsersRegisteredCompetition(const int) const {
    throw std::exception();
}
std::vector<ParticipantRepository::ParticipantAsUser> ParticipantRepository::getUsersConfirmedCompetition(const int) const {
    throw std::exception();
}

std::optional<ParticipantRepository::ParticipantAsUser> ParticipantRepository::getWinnerCategory(const int, const int) const {
    throw std::exception();
}

void ParticipantRepository::deleteUsersUnConfirmed(const int) const {
    throw std::exception();
}

bool ParticipantRepository::checkEveryoneWeighing(const int) const {
    throw std::exception();
}

bool ParticipantRepository::setCategory(const int, const int) const {
    throw std::exception();
}

std::vector<int> ParticipantRepository::getParticipantsByTeam(const int) const {
    throw std::exception();
}
std::optional<ParticipantRepository::Participant> ParticipantRepository::getParticipant(const int) const {
    throw std::exception();
}

} // namespace armai::infrastructure::repositories
