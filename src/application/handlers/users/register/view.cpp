#include "view.hpp"

#include <fmt/format.h>
#include <iostream>

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/utils/assert.hpp>

#include <jwt-cpp/jwt.h>

#include <application/mappers/users/requestToUserRegisterCommand.hpp>

#include <infrastructure/components/repositories/userRepositoryComponent.hpp>

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

		const auto bodyJson = userver::formats::json::FromString(request.RequestBody());
		const auto userRegisterCommand = mappers::users::getUserRegisterCommand(bodyJson);

		const auto idExistingUser = userRepository->getUserByEmail(userRegisterCommand.email);
		if (idExistingUser.has_value()) {
			response.SetStatus(userver::server::http::HttpStatus::kConflict);
			return {};
		}

		return bodyJson["name"].As<std::string>();
	}
};

} // namespace

void AppendUsersRegister(userver::components::ComponentList &component_list) {
	component_list.Append<UsersRegister>();
}

} // namespace armai
