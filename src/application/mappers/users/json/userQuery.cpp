#include "userQuery.hpp"

#include <userver/formats/json/inline.hpp>

namespace armai::application::mappers::users::json {

userver::formats::json::Value toJson(const UserQuery& user) {
    return userver::formats::json::MakeObject(
        "id", user.id,
        "name", user.name,
        "sex", domain::users::kStringFromSex.at(user.sex),
        "birth", userver::utils::datetime::ToString(user.birth),
        "isAdmin", user.isAdmin
    );
}

} // namespace armai::application::mappers::users::json
