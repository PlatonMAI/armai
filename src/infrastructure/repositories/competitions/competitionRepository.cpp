#include "competitionRepository.hpp"

#include <exception>

namespace armai::infrastructure::repositories {

int CompetitionRepository::createCompetition(const CompetitionCreateCommand&, const int) const {
    throw std::exception();
}
std::vector<CompetitionRepository::Competition> CompetitionRepository::getCompetitions() const {
    throw std::exception();
}
std::vector<CompetitionRepository::Competition> CompetitionRepository::getCompetitionsByStatus(const Status) const {
    throw std::exception();
}
std::optional<CompetitionRepository::Competition> CompetitionRepository::getCompetition(const int) const {
    throw std::exception();
}
bool CompetitionRepository::changeStatus(const int, const Status) const {
    throw std::exception();
}

} // namespace armai::infrastructure::repositories
