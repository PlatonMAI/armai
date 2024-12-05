#include "appendRepositories.hpp"

#include <infrastructure/components/repositories/userRepositoryComponent.hpp>

namespace armai::infrastructure::components {

void AppendRepositories(userver::components::ComponentList& component_list) {
    component_list.Append<UserRepositoryComponent>();
}

} // namespace armai::infrastructure::repositories
