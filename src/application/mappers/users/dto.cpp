#include "dto.hpp"

namespace armai::application::mappers::users::dto {

UserQuery queryFromDomain(const UserDomain& user) {
    return UserQuery{
        user.id,
        user.name,
        user.sex,
        user.birth,
        user.isAdmin,
        user.winsArmfights,
        user.winsCompetitions
    };
}

} // namespace armai::application::mappers::users::dto
