#pragma once

#include <vector>

#include <domain/categories/category.hpp>
#include <application/dto/categories/categoryCreateCommand.hpp>

namespace armai::infrastructure::repositories {

class CategoryRepository {
public:
    using Category = domain::categories::Category;
    using CategoryCreateCommand = application::dto::categories::CategoryCreateCommand;

    virtual int createCategory(const CategoryCreateCommand&) const;

    virtual std::vector<Category> getCategories(const int) const;
    virtual std::vector<Category> getCategoriesByCompetition(const int competitionId) const;
};

} // namespace armai::infrastructure::repositories
