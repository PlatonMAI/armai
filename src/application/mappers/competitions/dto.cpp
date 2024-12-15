#include "dto.hpp"

namespace armai::application::mappers::competitions::dto {

CompetitionMulQuery mulQueryFromDomain(const CompetitionDomain& competitionDomain) {
    return {
        competitionDomain.id,
        competitionDomain.name,
        competitionDomain.status
    };
}
CompetitionQuery queryFromDomain(const CompetitionDomain& competitionDomain) {
    return {
        competitionDomain.id,
        competitionDomain.name,
        competitionDomain.hand,
        competitionDomain.status
    };
}

} // namespace armai::application::mappers::competitions::dto
