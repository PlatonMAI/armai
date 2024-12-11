#include "categoryRepositoryComponent.hpp"

namespace armai::infrastructure::components {

std::shared_ptr<repositories::CategoryRepository> CategoryRepositoryComponent::GetCategoryRepository() const {
    return category_repository_;
}

} // namespace armai::infrastructure::components
