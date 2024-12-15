#include "dto.hpp"

namespace armai::application::mappers::armfights::dto {

ArmfightQuery queryFromDomain(const ArmfightDomain& armfightDomain) {
    return {
        armfightDomain.id.value(),
        armfightDomain.participantFirstId.value(),
        armfightDomain.participantSecondId.value(),
        armfightDomain.hand
    };
}

} // namespace armai::application::mappers::armfights::dto
