#include "view.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/server/http/http_method.hpp>

#include <application/utils/auth.hpp>
#include <application/utils/competitions.hpp>
#include <application/mappers/competitions/dto.hpp>
#include <application/mappers/competitions/json.hpp>
#include <application/mappers/categories/dto.hpp>
#include <infrastructure/components/repositories/competitionRepositoryComponent.hpp>
#include <infrastructure/components/repositories/participantRepositoryComponent.hpp>
#include <infrastructure/components/repositories/categoryRepositoryComponent.hpp>
#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <infrastructure/components/repositories/armfightRepositoryComponent.hpp>
#include <domain/utils/jwt.hpp>
#include <domain/competitions/competitions.hpp>

namespace armai::application::handlers {
	
namespace {

class CompetitionsIdChangeStatus final : public userver::server::handlers::HttpHandlerBase {
private:
	using CompetitionRepository = infrastructure::repositories::CompetitionRepository;
	std::shared_ptr<CompetitionRepository> competitionRepository;
	using ParticipantRepository = infrastructure::repositories::ParticipantRepository;
	std::shared_ptr<ParticipantRepository> participantRepository;
	using CategoryRepository = infrastructure::repositories::CategoryRepository;
	std::shared_ptr<CategoryRepository> categoryRepository;
	using ArmfightRepository = infrastructure::repositories::ArmfightRepository;
	std::shared_ptr<ArmfightRepository> armfightRepository;

public:
	static constexpr std::string_view kName = "handler-competitions-id-change_status";

	CompetitionsIdChangeStatus(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		competitionRepository( component_context.FindComponent<armai::infrastructure::components::CompetitionRepositoryComponent>().GetCompetitionRepository() ),
		participantRepository( component_context.FindComponent<armai::infrastructure::components::ParticipantRepositoryComponent>().GetParticipantRepository() ),
		categoryRepository( component_context.FindComponent<armai::infrastructure::components::CategoryRepositoryComponent>().GetCategoryRepository() ),
		armfightRepository( component_context.FindComponent<armai::infrastructure::components::ArmfightRepositoryComponent>().GetArmfightRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		LOG_WARNING() << "CompetitionsIdChangeStatus: start";

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

		if (!(competition.value().ownerId == claims.userId || claims.isAdmin)) {
			response.SetStatus(userver::server::http::HttpStatus::kForbidden);
			return {};
		}

		switch (competition.value().status) {
			case domain::competitions::kRegistration:
				return utils::competitions::changeStatusRegistration(competitionId, competitionRepository);
				break;
			case domain::competitions::kConfirmation:
				return utils::competitions::changeStatusConfirmation(competitionId, competitionRepository, participantRepository);
				break;
			case domain::competitions::kWeighing:
				return utils::competitions::changeStatusWeighing(response, competitionId, competition.value().hand, competitionRepository, participantRepository, categoryRepository, armfightRepository);
				break;
			case domain::competitions::kInProcess:
				return utils::competitions::changeStatusInProcess(competitionId, competitionRepository);
				break;
			default:
				throw userver::server::handlers::ClientError(
					userver::server::handlers::ExternalBody{fmt::format("Unsupported competition status {}", request.GetMethod())}
				);
		}
	}
};

} // namespace

void AppendCompetitionsIdChangeStatus(userver::components::ComponentList &component_list) {
	component_list.Append<CompetitionsIdChangeStatus>();
}

} // namespace armai::application::handlers
