#include "appendHandlers.hpp"

#include <application/handlers/users/register/view.hpp>
#include <application/handlers/users/auth/view.hpp>
#include <application/handlers/users/logout/view.hpp>
#include <application/handlers/users/me/view.hpp>
#include <application/handlers/users/me/is_admin/view.hpp>
#include <application/handlers/users/id/view.hpp>

#include <application/handlers/category_schemas/view.hpp>
#include <application/handlers/category_schemas/id/view.hpp>

#include <application/handlers/teams/view.hpp>
#include <application/handlers/teams/id/view.hpp>

#include <application/handlers/competitions/view.hpp>
#include <application/handlers/competitions/id/view.hpp>
#include <application/handlers/competitions/id/register/view.hpp>
#include <application/handlers/competitions/id/register/check/view.hpp>
#include <application/handlers/competitions/id/register/users/view.hpp>
#include <application/handlers/competitions/id/confirmation/view.hpp>
#include <application/handlers/competitions/id/confirmation/check/view.hpp>
#include <application/handlers/competitions/id/confirmation/users/view.hpp>
#include <application/handlers/competitions/id/weighing/view.hpp>
#include <application/handlers/competitions/id/categories/view.hpp>
#include <application/handlers/competitions/id/categories/id/view.hpp>
#include <application/handlers/competitions/id/categories/id/winner/view.hpp>
#include <application/handlers/competitions/id/change_status/view.hpp>

namespace armai::application::handlers {

void AppendHandlers(userver::components::ComponentList& component_list) {
    AppendUsersRegister(component_list);
    AppendUsersAuth(component_list);
    AppendUsersLogout(component_list);
    AppendUsersMe(component_list);
    AppendUsersMeIsAdmin(component_list);
    AppendUsersId(component_list);
    

    AppendCategorySchemas(component_list);
    AppendCategorySchemasId(component_list);

    
    AppendTeams(component_list);
    AppendTeamsId(component_list);


    AppendCompetitions(component_list);
    AppendCompetitionsId(component_list);

    AppendCompetitionsIdRegister(component_list);
    AppendCompetitionsIdRegisterCheck(component_list);
    AppendCompetitionsIdRegisterUsers(component_list);

    AppendCompetitionsIdConfirmation(component_list);
    AppendCompetitionsIdConfirmationCheck(component_list);
    AppendCompetitionsIdConfirmationUsers(component_list);
    
    AppendCompetitionsIdCategories(component_list);
    AppendCompetitionsIdCategoriesId(component_list);
    AppendCompetitionsIdCategoriesIdWinner(component_list);
    
    AppendCompetitionsIdWeighing(component_list);
    
    AppendCompetitionsIdChangeStatus(component_list);
}

} // namespace armai::application::handlers
