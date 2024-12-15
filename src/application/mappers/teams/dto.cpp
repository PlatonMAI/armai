#include "dto.hpp"

namespace armai::application::mappers::teams::dto {

TeamMulQuery mulQueryFromDomain(const TeamDomain& teamDomain) {
    return {
        teamDomain.id,
        teamDomain.name
    };
}
TeamQuery queryFromDomain(const TeamDomain& teamDomain) {
    return {
        teamDomain.id,
        teamDomain.name,
        teamDomain.winsArmfights,
        teamDomain.winsCompetitions,
        {}
    };
}

} // namespace armai::application::mappers::teams::dto
