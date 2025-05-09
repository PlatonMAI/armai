#include "view.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

#include <application/utils/auth.hpp>
#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <infrastructure/components/repositories/redisRepositoryComponent.hpp>
#include <domain/utils/auth.hpp>
#include <domain/utils/jwt.hpp>
#include <domain/utils/exceptions/authExceptions/auth.hpp>

namespace armai::application::handlers {
	
namespace {

class UsersLogout final : public userver::server::handlers::HttpHandlerBase {
private:
	std::shared_ptr<armai::infrastructure::repositories::UserRepository> userRepository;
	std::shared_ptr<armai::infrastructure::repositories::redis::RedisRepository> redisRepository;

public:
	static constexpr std::string_view kName = "handler-users-logout";

	UsersLogout(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		userRepository( component_context.FindComponent<armai::infrastructure::components::UserRepositoryComponent>().GetUserRepository() ),
		redisRepository( component_context.FindComponent<armai::infrastructure::components::RedisRepositoryComponent>().GetRedisRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		auto &response = request.GetHttpResponse();
        const auto claims = utils::auth::checkAuth(request, response, redisRepository);

		redisRepository->DelRefresh(claims.userId);

        response.SetCookie(
            utils::auth::buildCookieToken(utils::auth::kJwtCookieName, "")
            .SetExpires(std::chrono::system_clock::time_point(std::chrono::system_clock::now()))
        );
		response.SetCookie(
            utils::auth::buildCookieToken(utils::auth::kRefreshCookieName, "")
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
