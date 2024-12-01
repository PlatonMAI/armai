#pragma once

#include <userver/storages/postgres/cluster.hpp>

#include "userRepository.hpp"

namespace armai::infrastructure::repositories::users {

class UserRepositoryPostgres : public UserRepository {
public:
    UserRepositoryPostgres(const userver::storages::postgres::ClusterPtr pg_cluster) : pg_cluster_(pg_cluster) {}

    std::optional<int> getUserByEmail(const std::string&) const override final;

private:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace armai::infrastructure::repositories::users
