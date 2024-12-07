#pragma once

#include <userver/storages/postgres/cluster.hpp>

#include <infrastructure/repositories/categorySchemas/categorySchemaRepository.hpp>

namespace armai::infrastructure::repositories::categorySchemas {

class CategorySchemaRepositoryPostgres : public CategorySchemaRepository {
public:
    CategorySchemaRepositoryPostgres(const userver::storages::postgres::ClusterPtr pg_cluster) : pg_cluster_(pg_cluster) {}

    // std::optional<UserDomain> getUserById(const int) const override final;

    virtual int createSchema(const CategorySchemaCreateCommand&) const override final;

private:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace armai::infrastructure::repositories::categorySchemas
