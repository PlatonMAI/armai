#include "view.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/server/http/http_method.hpp>

#include <infrastructure/components/repositories/competitionRepositoryComponent.hpp>
#include <infrastructure/components/repositories/redisRepositoryComponent.hpp>
#include <application/utils/auth.hpp>
#include <application/utils/competitions.hpp>
#include <domain/utils/jwt.hpp>

namespace armai::application::handlers {
	
namespace {

class Competitions final : public userver::server::handlers::HttpHandlerBase {
private:
	std::shared_ptr<infrastructure::repositories::CompetitionRepository> competitionRepository;
	std::shared_ptr<infrastructure::repositories::redis::RedisRepository> redisRepository;

public:
	static constexpr std::string_view kName = "handler-competitions";

	Competitions(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		competitionRepository( component_context.FindComponent<armai::infrastructure::components::CompetitionRepositoryComponent>().GetCompetitionRepository() ),
		redisRepository( component_context.FindComponent<armai::infrastructure::components::RedisRepositoryComponent>().GetRedisRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		auto &response = request.GetHttpResponse();
		const auto claims = utils::auth::checkAuth(request, response, redisRepository);

		switch (request.GetMethod()) {
			case userver::server::http::HttpMethod::kPost:
				LOG_WARNING() << "Competitions: kPost";
				response.SetHeader((std::string)"Content-Type", (std::string)"application/json");
				return utils::competitions::createCompetition(request, claims.userId, competitionRepository);
			case userver::server::http::HttpMethod::kGet:
				LOG_WARNING() << "Competitions: kGet";
				response.SetHeader((std::string)"Content-Type", (std::string)"application/json");

				if (request.HasArg("status")) {
					return utils::competitions::getCompetitionsByStatus(request, competitionRepository);
				} else {
					return utils::competitions::getCompetitions(competitionRepository);
				}
			default:
				throw userver::server::handlers::ClientError(
					userver::server::handlers::ExternalBody{fmt::format("Unsupported method {}", request.GetMethod())}
				);
		}
	}
};

} // namespace

void AppendCompetitions(userver::components::ComponentList &component_list) {
	component_list.Append<Competitions>();
}

} // namespace armai::application::handlers
