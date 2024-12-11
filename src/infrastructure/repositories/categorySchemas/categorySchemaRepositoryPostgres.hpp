#pragma once

#include <userver/storages/postgres/cluster.hpp>

#include <infrastructure/repositories/categorySchemas/categorySchemaRepository.hpp>

namespace armai::infrastructure::repositories::categorySchemas {

class CategorySchemaRepositoryPostgres : public CategorySchemaRepository {
public:
    CategorySchemaRepositoryPostgres(const userver::storages::postgres::ClusterPtr pg_cluster) : pg_cluster_(pg_cluster) {}

    virtual int createSchema(const CategorySchemaCreateCommand&, const int ownerId) const override final;

    virtual std::vector<CategorySchema> getSchemas() const override final;
    virtual std::optional<CategorySchema> getSchema(const int) const override final;

private:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace armai::infrastructure::repositories::categorySchemas
