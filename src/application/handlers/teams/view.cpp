#include "view.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/server/http/http_method.hpp>

#include <infrastructure/components/repositories/teamRepositoryComponent.hpp>
#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <application/utils/auth.hpp>
#include <application/utils/teams.hpp>
#include <domain/utils/jwt.hpp>

namespace armai::application::handlers {
	
namespace {

class Teams final : public userver::server::handlers::HttpHandlerBase {
private:
	using TeamRepository = infrastructure::repositories::TeamRepository;
	std::shared_ptr<TeamRepository> teamRepository;

public:
	static constexpr std::string_view kName = "handler-teams";

	Teams(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		teamRepository( component_context.FindComponent<armai::infrastructure::components::TeamRepositoryComponent>().GetTeamRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		LOG_WARNING() << "Teams: start";

		auto &response = request.GetHttpResponse();

		if (!utils::auth::checkExistsJwt(request)) {
			response.SetStatus(userver::server::http::HttpStatus::kUnauthorized);
			return {};
		}

		const auto jwt = utils::auth::getJwt(request);
        const auto claims = domain::utils::jwt::decodeJwt(jwt.value());

		switch (request.GetMethod()) {
			case userver::server::http::HttpMethod::kPost:
				LOG_WARNING() << "Teams: kPost";
				response.SetHeader((std::string)"Content-Type", (std::string)"application/json");
				return utils::teams::createTeam(request, claims.userId, teamRepository);
			case userver::server::http::HttpMethod::kGet:
				LOG_WARNING() << "Teams: kGet";
				response.SetHeader((std::string)"Content-Type", (std::string)"application/json");
				return utils::teams::getTeams(teamRepository);
			default:
				throw userver::server::handlers::ClientError(
					userver::server::handlers::ExternalBody{fmt::format("Unsupported method {}", request.GetMethod())}
				);
		}
	}
};

} // namespace

void AppendTeams(userver::components::ComponentList &component_list) {
	component_list.Append<Teams>();
}

} // namespace armai::application::handlers
