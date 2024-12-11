#include "appendRepositories.hpp"

#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <infrastructure/components/repositories/categorySchemaRepositoryComponent.hpp>
#include <infrastructure/components/repositories/categoryRepositoryComponent.hpp>

namespace armai::infrastructure::components {

void AppendRepositories(userver::components::ComponentList& component_list) {
    component_list.Append<UserRepositoryComponent>();
    component_list.Append<CategorySchemaRepositoryComponent>();
    component_list.Append<CategoryRepositoryComponent>();
}

} // namespace armai::infrastructure::repositories
