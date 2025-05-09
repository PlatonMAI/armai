#include "view.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/server/http/http_method.hpp>

#include <application/utils/auth.hpp>
#include <application/mappers/participants/request.hpp>
#include <infrastructure/components/repositories/competitionRepositoryComponent.hpp>
#include <infrastructure/components/repositories/participantRepositoryComponent.hpp>
#include <infrastructure/components/repositories/redisRepositoryComponent.hpp>
#include <domain/utils/jwt.hpp>

namespace armai::application::handlers {
	
namespace {

class CompetitionsIdRegisterCheck final : public userver::server::handlers::HttpHandlerBase {
private:
	std::shared_ptr<infrastructure::repositories::CompetitionRepository> competitionRepository;
	std::shared_ptr<infrastructure::repositories::ParticipantRepository> participantRepository;
	std::shared_ptr<infrastructure::repositories::redis::RedisRepository> redisRepository;

public:
	static constexpr std::string_view kName = "handler-competitions-id-register-check";

	CompetitionsIdRegisterCheck(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		competitionRepository( component_context.FindComponent<armai::infrastructure::components::CompetitionRepositoryComponent>().GetCompetitionRepository() ),
		participantRepository( component_context.FindComponent<armai::infrastructure::components::ParticipantRepositoryComponent>().GetParticipantRepository() ),
		redisRepository( component_context.FindComponent<armai::infrastructure::components::RedisRepositoryComponent>().GetRedisRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		auto &response = request.GetHttpResponse();
		const auto claims = utils::auth::checkAuth(request, response, redisRepository);

		const auto competitionId = std::stoi(request.GetPathArg(0));

		const auto competition = competitionRepository->getCompetition(competitionId);
        if (!competition.has_value()) {
            response.SetStatus(userver::server::http::HttpStatus::kNotFound);
			return {};
        }

		const auto isRegister = participantRepository->checkRegisterParticipant(competitionId, claims.userId);
		if (!isRegister) {
			response.SetStatus(userver::server::http::HttpStatus::kNotFound);
			return {};
		}

        return {};
	}
};

} // namespace

void AppendCompetitionsIdRegisterCheck(userver::components::ComponentList &component_list) {
	component_list.Append<CompetitionsIdRegisterCheck>();
}

} // namespace armai::application::handlers
