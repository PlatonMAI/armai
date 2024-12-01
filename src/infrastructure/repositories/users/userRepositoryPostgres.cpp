#include "userRepositoryPostgres.hpp"

#include <infrastructure/queries/users/usersRead.hpp>

namespace armai::infrastructure::repositories::users {

std::optional<int> UserRepositoryPostgres::getUserByEmail(const std::string& email) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::kSelectUserByEmail, email);
    if (res.IsEmpty()) {
        return {};
    }

    return res.AsSingleRow<int>();
}

} // namespace armai::infrastructure::repositories::users
