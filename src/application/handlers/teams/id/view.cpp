#include "view.hpp"

#include <exception>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/server/http/http_method.hpp>

#include <application/utils/auth.hpp>
#include <application/utils/teams.hpp>
#include <application/mappers/teams/dto.hpp>
#include <application/mappers/teams/json.hpp>
#include <application/mappers/categories/dto.hpp>
#include <infrastructure/components/repositories/teamRepositoryComponent.hpp>
#include <infrastructure/components/repositories/participantRepositoryComponent.hpp>
#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <domain/utils/jwt.hpp>

namespace armai::application::handlers {
	
namespace {

class TeamsId final : public userver::server::handlers::HttpHandlerBase {
private:
	using TeamRepository = infrastructure::repositories::TeamRepository;
	std::shared_ptr<TeamRepository> teamRepository;
	using ParticipantRepository = infrastructure::repositories::ParticipantRepository;
	std::shared_ptr<ParticipantRepository> participantRepository;
	using UserRepository = infrastructure::repositories::UserRepository;
	std::shared_ptr<UserRepository> userRepository;

public:
	static constexpr std::string_view kName = "handler-teams-id";

	TeamsId(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		teamRepository( component_context.FindComponent<armai::infrastructure::components::TeamRepositoryComponent>().GetTeamRepository() ),
		participantRepository( component_context.FindComponent<armai::infrastructure::components::ParticipantRepositoryComponent>().GetParticipantRepository() ),
		userRepository( component_context.FindComponent<armai::infrastructure::components::UserRepositoryComponent>().GetUserRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		LOG_WARNING() << "TeamsId: start";

		auto &response = request.GetHttpResponse();

		if (!utils::auth::checkExistsJwt(request)) {
			response.SetStatus(userver::server::http::HttpStatus::kUnauthorized);
			return {};
		}

		const auto jwt = utils::auth::getJwt(request);
        domain::utils::jwt::decodeJwt(jwt.value());

		const auto team = teamRepository->getTeam(std::stoi(request.GetPathArg(0)));
        if (!team.has_value()) {
            response.SetStatus(userver::server::http::HttpStatus::kNotFound);
			return {};
        }

        auto teamQuery = application::mappers::teams::dto::queryFromDomain(team.value());

        const auto userIds = participantRepository->getParticipantsByTeam(teamQuery.id);
        for (const auto userId : userIds) {
            const auto user = userRepository->getUserById(userId);
			if (!user.has_value()) {
				// "не найден пользователь, являющийся участником соревнований"
				throw std::exception();
			}

			teamQuery.participants.push_back({
				user.value().id,
				user.value().name
			});
        }

        response.SetHeader((std::string)"Content-Type", (std::string)"application/json");

        return userver::formats::json::ToString(
            mappers::teams::json::toJson(teamQuery)
        );
	}
};

} // namespace

void AppendTeamsId(userver::components::ComponentList &component_list) {
	component_list.Append<TeamsId>();
}

} // namespace armai::application::handlers
