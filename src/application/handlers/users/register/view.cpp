#include "view.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

#include <application/utils/auth.hpp>
#include <application/mappers/users/request/userRegisterCommand.hpp>
#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <domain/utils/auth.hpp>
#include <domain/utils/jwt.hpp>

namespace armai::application::handlers {
	
namespace {

class UsersRegister final : public userver::server::handlers::HttpHandlerBase {
private:
	using UserRepository = armai::infrastructure::repositories::UserRepository;
	std::shared_ptr<UserRepository> userRepository;

public:
	static constexpr std::string_view kName = "handler-users-register";

	UsersRegister(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		userRepository( component_context.FindComponent<armai::infrastructure::components::UserRepositoryComponent>().GetUserRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		auto &response = request.GetHttpResponse();

		if (utils::auth::checkExistsJwt(request)) {
			response.SetStatus(userver::server::http::HttpStatus::kForbidden);
			return {};
		}

		const auto bodyJson = userver::formats::json::FromString(request.RequestBody());
		auto userRegisterCommand = mappers::users::request::getUserRegisterCommand(bodyJson);

		const auto existingUser = userRepository->getUserByEmail(userRegisterCommand.email);
		if (existingUser.has_value()) {
			response.SetStatus(userver::server::http::HttpStatus::kConflict);
			return {};
		}

		userRegisterCommand.password = domain::utils::auth::getHashPassword(userRegisterCommand.password);
		const auto userId = userRepository->createUser(userRegisterCommand);

		const auto jwt = domain::utils::jwt::createJwt({userId, false});
		response.SetCookie(utils::auth::buildCookieJwt(jwt));

		return {};
	}
};

} // namespace

void AppendUsersRegister(userver::components::ComponentList &component_list) {
	component_list.Append<UsersRegister>();
}

} // namespace armai::application::handlers
