#include "userDomainQuery.hpp"

namespace armai::application::mappers::users {

UserQuery toQuery(const UserDomain& user) {
    return UserQuery{
        user.id,
        user.name,
        user.sex,
        user.birth,
        user.isAdmin
    };
}

} // namespace armai::application::mappers::users
