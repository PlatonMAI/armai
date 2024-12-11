#include "appendHandlers.hpp"

#include <application/handlers/users/register/view.hpp>
#include <application/handlers/users/auth/view.hpp>
#include <application/handlers/users/logout/view.hpp>
#include <application/handlers/users/me/view.hpp>
#include <application/handlers/users/id/view.hpp>

#include <application/handlers/category_schemas/view.hpp>
#include <application/handlers/category_schemas/id/view.hpp>

namespace armai::application::handlers {

void AppendHandlers(userver::components::ComponentList& component_list) {
    AppendUsersRegister(component_list);
    AppendUsersAuth(component_list);
    AppendUsersLogout(component_list);
    AppendUsersMe(component_list);
    AppendUsersId(component_list);

    AppendCategorySchemas(component_list);
    AppendCategorySchemasId(component_list);
}

} // namespace armai::application::handlers
