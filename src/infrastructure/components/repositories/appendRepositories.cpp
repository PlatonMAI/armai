#include "appendRepositories.hpp"

namespace armai::infrastructure::components {

void AppendUserRepository(userver::components::ComponentList& component_list) {
    component_list.Append<UserRepositoryComponent>();
}

} // namespace namespace armai::infrastructure::repositories
