#include "categoryRepository.hpp"

#include <exception>

namespace armai::infrastructure::repositories {

int CategoryRepository::createCategory(const CategoryCreateCommand&) const {
    throw std::exception();
}

std::vector<CategoryRepository::Category> CategoryRepository::getCategories(const int) const {
    throw std::exception();
}
std::vector<CategoryRepository::Category> CategoryRepository::getCategoriesByCompetition(const int) const {
    throw std::exception();
}

} // namespace armai::infrastructure::repositories
