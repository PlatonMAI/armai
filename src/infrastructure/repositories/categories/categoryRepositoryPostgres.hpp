#pragma once

#include <userver/storages/postgres/cluster.hpp>

#include <infrastructure/repositories/categories/categoryRepository.hpp>

namespace armai::infrastructure::repositories::categories {

class CategoryRepositoryPostgres : public CategoryRepository {
public:
    CategoryRepositoryPostgres(const userver::storages::postgres::ClusterPtr pg_cluster) : pg_cluster_(pg_cluster) {}

    virtual int createCategory(const CategoryCreateCommand&) const override final;

    virtual std::vector<Category> getCategories(const int) const override final;
    virtual std::vector<Category> getCategoriesByCompetition(const int competitionId) const override final;

private:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace armai::infrastructure::repositories::categories
