#include "user.hpp"

#include <userver/formats/json/inline.hpp>

namespace armai::application::mappers::users::json {

userver::formats::json::Value toJson(const UserDomain& user) {
    return userver::formats::json::MakeObject(
        "id", user.id,
        "email", user.email,
        "password", user.password,
        "name", user.name,
        // "sex", user.sex,
        "birth", userver::utils::datetime::ToString(user.birth),
        "isAdmin", user.isAdmin
    );
}

} // namespace armai::application::mappers::users::json
