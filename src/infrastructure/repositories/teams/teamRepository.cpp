#include "teamRepository.hpp"

#include <exception>

namespace armai::infrastructure::repositories {

int TeamRepository::createTeam(const TeamCreateCommand&, const int) const {
    throw std::exception();
}
std::vector<TeamRepository::Team> TeamRepository::getTeams() const {
    throw std::exception();
}
std::optional<TeamRepository::Team> TeamRepository::getTeam(const int) const {
    throw std::exception();
}

} // namespace armai::infrastructure::repositories
