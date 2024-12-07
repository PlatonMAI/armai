#include "appendRepositories.hpp"

#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <infrastructure/components/repositories/categorySchemaRepositoryComponent.hpp>

namespace armai::infrastructure::components {

void AppendRepositories(userver::components::ComponentList& component_list) {
    component_list.Append<UserRepositoryComponent>();
    component_list.Append<CategorySchemaRepositoryComponent>();
}

} // namespace armai::infrastructure::repositories
