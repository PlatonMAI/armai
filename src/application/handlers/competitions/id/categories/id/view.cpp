#include "view.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/server/http/http_method.hpp>

#include <application/utils/auth.hpp>
#include <application/utils/competitions.hpp>
#include <application/dto/armfights/armfightWinCommand.hpp>
#include <application/mappers/competitions/dto.hpp>
#include <application/mappers/competitions/json.hpp>
#include <infrastructure/components/repositories/competitionRepositoryComponent.hpp>
#include <infrastructure/components/repositories/participantRepositoryComponent.hpp>
#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <infrastructure/components/repositories/armfightRepositoryComponent.hpp>
#include <infrastructure/components/repositories/redisRepositoryComponent.hpp>
#include <domain/utils/jwt.hpp>
#include <domain/competitions/competitions.hpp>

namespace armai::application::handlers {
	
namespace {

class CompetitionsIdCategoriesId final : public userver::server::handlers::HttpHandlerBase {
private:
	std::shared_ptr<infrastructure::repositories::CompetitionRepository> competitionRepository;
	std::shared_ptr<infrastructure::repositories::ArmfightRepository> armfightRepository;
	std::shared_ptr<infrastructure::repositories::ParticipantRepository> participantRepository;
	std::shared_ptr<infrastructure::repositories::UserRepository> userRepository;
	std::shared_ptr<infrastructure::repositories::redis::RedisRepository> redisRepository;

public:
	static constexpr std::string_view kName = "handler-competitions-id-categories-id";

	CompetitionsIdCategoriesId(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		competitionRepository( component_context.FindComponent<armai::infrastructure::components::CompetitionRepositoryComponent>().GetCompetitionRepository() ),
		armfightRepository( component_context.FindComponent<armai::infrastructure::components::ArmfightRepositoryComponent>().GetArmfightRepository() ),
		participantRepository( component_context.FindComponent<armai::infrastructure::components::ParticipantRepositoryComponent>().GetParticipantRepository() ),
		userRepository( component_context.FindComponent<armai::infrastructure::components::UserRepositoryComponent>().GetUserRepository() ),
		redisRepository( component_context.FindComponent<armai::infrastructure::components::RedisRepositoryComponent>().GetRedisRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		auto &response = request.GetHttpResponse();
		const auto claims = utils::auth::checkAuth(request, response, redisRepository);

		const auto competitionId = std::stoi(request.GetPathArg(0));
		const auto competition = competitionRepository->getCompetition(competitionId);

		if (!(competition.value().ownerId == claims.userId || claims.isAdmin)) {
			response.SetStatus(userver::server::http::HttpStatus::kForbidden);
			return {};
		}
        if (!competition.has_value()) {
            response.SetStatus(userver::server::http::HttpStatus::kNotFound);
			return {};
        }
		if (competition.value().status != domain::competitions::kInProcess && competition.value().status != domain::competitions::kFinished) {
			response.SetStatus(userver::server::http::HttpStatus::kBadRequest);
			return {};
		}

		switch (request.GetMethod()) {
			case userver::server::http::HttpMethod::kPost:
				LOG_WARNING() << "Competitions: kPost";
				return utils::competitions::winArmfight(response, request, armfightRepository);
			case userver::server::http::HttpMethod::kGet:
				LOG_WARNING() << "Competitions: kGet";
				response.SetHeader((std::string)"Content-Type", (std::string)"application/json");
				return utils::competitions::getArmfight(response, request, participantRepository, userRepository, armfightRepository);
			default:
				throw userver::server::handlers::ClientError(
					userver::server::handlers::ExternalBody{fmt::format("Unsupported method {}", request.GetMethod())}
				);
		}
	}
};

} // namespace

void AppendCompetitionsIdCategoriesId(userver::components::ComponentList &component_list) {
	component_list.Append<CompetitionsIdCategoriesId>();
}

} // namespace armai::application::handlers
