#include "view.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

#include <application/utils/auth.hpp>
#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <domain/utils/auth.hpp>
#include <domain/utils/jwt.hpp>

namespace armai::application::handlers {
	
namespace {

class UsersLogout final : public userver::server::handlers::HttpHandlerBase {
private:
	using UserRepository = armai::infrastructure::repositories::UserRepository;
	std::shared_ptr<UserRepository> userRepository;

public:
	static constexpr std::string_view kName = "handler-users-logout";

	UsersLogout(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		userRepository( component_context.FindComponent<armai::infrastructure::components::UserRepositoryComponent>().GetUserRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		auto &response = request.GetHttpResponse();
        
        if (!utils::auth::checkExistsJwt(request)) {
			response.SetStatus(userver::server::http::HttpStatus::kUnauthorized);
			return {};
		}

        response.SetCookie(
            utils::auth::buildCookieJwt("")
            .SetExpires(std::chrono::system_clock::time_point(std::chrono::system_clock::now()))
        );
		
        return {};
	}
};

} // namespace

void AppendUsersLogout(userver::components::ComponentList &component_list) {
	component_list.Append<UsersLogout>();
}

} // namespace armai::application::handlers
