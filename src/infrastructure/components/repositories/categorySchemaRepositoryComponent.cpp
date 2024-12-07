#include "categorySchemaRepositoryComponent.hpp"

namespace armai::infrastructure::components {

std::shared_ptr<repositories::CategorySchemaRepository> CategorySchemaRepositoryComponent::GetCategorySchemaRepository() const {
    return category_schema_repository_;
}

} // namespace armai::infrastructure::components
