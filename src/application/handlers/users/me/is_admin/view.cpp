#include "view.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/formats/json/inline.hpp>
#include <userver/formats/json/serialize.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

#include <application/utils/auth.hpp>
#include <application/mappers/users/request.hpp>
#include <application/mappers/users/dto.hpp>
#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <domain/utils/auth.hpp>
#include <domain/utils/jwt.hpp>
#include <application/mappers/users/json.hpp>

namespace armai::application::handlers {
	
namespace {

class UsersMeIsAdmin final : public userver::server::handlers::HttpHandlerBase {
private:
	using UserRepository = armai::infrastructure::repositories::UserRepository;
	std::shared_ptr<UserRepository> userRepository;

public:
	static constexpr std::string_view kName = "handler-users-me-is_admin";

	UsersMeIsAdmin(
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

        const auto jwt = utils::auth::getJwt(request);
        const auto claims = domain::utils::jwt::decodeJwt(jwt.value());

        response.SetHeader((std::string)"Content-Type", (std::string)"application/json");

        return userver::formats::json::ToString(
            userver::formats::json::MakeObject(
				"isAdmin", claims.isAdmin
			)
        );
	}
};

} // namespace

void AppendUsersMeIsAdmin(userver::components::ComponentList &component_list) {
	component_list.Append<UsersMeIsAdmin>();
}

} // namespace armai::application::handlers
