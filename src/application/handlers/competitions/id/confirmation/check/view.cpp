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
#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <domain/utils/jwt.hpp>

namespace armai::application::handlers {
	
namespace {

class CompetitionsIdConfirmationCheck final : public userver::server::handlers::HttpHandlerBase {
private:
	using CompetitionRepository = infrastructure::repositories::CompetitionRepository;
	std::shared_ptr<CompetitionRepository> competitionRepository;
	using ParticipantRepository = infrastructure::repositories::ParticipantRepository;
	std::shared_ptr<ParticipantRepository> participantRepository;

public:
	static constexpr std::string_view kName = "handler-competitions-id-confirmation-check";

	CompetitionsIdConfirmationCheck(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		competitionRepository( component_context.FindComponent<armai::infrastructure::components::CompetitionRepositoryComponent>().GetCompetitionRepository() ),
		participantRepository( component_context.FindComponent<armai::infrastructure::components::ParticipantRepositoryComponent>().GetParticipantRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		LOG_WARNING() << "CompetitionsIdConfirmationCheck: start";

		auto &response = request.GetHttpResponse();

		if (!utils::auth::checkExistsJwt(request)) {
			response.SetStatus(userver::server::http::HttpStatus::kUnauthorized);
			return {};
		}

		const auto jwt = utils::auth::getJwt(request);
        const auto claims = domain::utils::jwt::decodeJwt(jwt.value());

		const auto competitionId = std::stoi(request.GetPathArg(0));

		const auto competition = competitionRepository->getCompetition(competitionId);
        if (!competition.has_value()) {
            response.SetStatus(userver::server::http::HttpStatus::kNotFound);
			return {};
        }

		const auto isConfirmation = participantRepository->checkConfirmationParticipant(competitionId, claims.userId);
		if (!isConfirmation) {
			response.SetStatus(userver::server::http::HttpStatus::kNotFound);
			return {};
		}

        return {};
	}
};

} // namespace

void AppendCompetitionsIdConfirmationCheck(userver::components::ComponentList &component_list) {
	component_list.Append<CompetitionsIdConfirmationCheck>();
}

} // namespace armai::application::handlers
