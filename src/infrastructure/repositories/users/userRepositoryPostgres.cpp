#include "userRepositoryPostgres.hpp"

#include <userver/storages/postgres/io/row_types.hpp>
#include <userver/storages/postgres/parameter_store.hpp>
#include <userver/storages/postgres/io/date.hpp>

#include <infrastructure/queries/users/usersRead.hpp>
#include <infrastructure/queries/users/usersCreate.hpp>
#include <infrastructure/mappers/users/parameterStore.hpp>
#include <infrastructure/mappers/postgres/sex.hpp>

namespace armai::infrastructure::repositories::users {

std::optional<UserRepositoryPostgres::UserDomain> UserRepositoryPostgres::getUserByEmail(const std::string& email) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::users::kSelectUserByEmail, email);
    if (res.IsEmpty()) {
        return {};
    }

    return res.AsOptionalSingleRow<UserDomain>(userver::storages::postgres::kRowTag);
}
std::optional<UserRepositoryPostgres::UserDomain> UserRepositoryPostgres::getUserById(const int id) const {
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kSlave, queries::users::kSelectUserById, id);
    if (res.IsEmpty()) {
        return {};
    }

    return res.AsOptionalSingleRow<UserDomain>(userver::storages::postgres::kRowTag);
}

int UserRepositoryPostgres::createUser(const UserRegisterCommand& user) const {
    const auto parameterStore = mappers::users::parameterStore::toStore(user);
    const auto res = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, queries::users::kCreateUser, parameterStore);

    return res.AsSingleRow<int>();
}

} // namespace armai::infrastructure::repositories::users
