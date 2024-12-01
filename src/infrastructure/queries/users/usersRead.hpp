#include <string>

#include <userver/storages/postgres/query.hpp>

namespace armai::infrastructure::queries {

    const userver::storages::postgres::Query kSelectUserByEmail{
        "SELECT id "
        "FROM users "
        "WHERE email = $1",
        userver::storages::postgres::Query::Name{"select_user_by_email"}
    };

} // namespace armai::infrastructure::repositories
