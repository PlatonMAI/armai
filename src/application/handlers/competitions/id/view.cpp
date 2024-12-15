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
#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <domain/utils/jwt.hpp>

namespace armai::application::handlers {
	
namespace {

class CompetitionsId final : public userver::server::handlers::HttpHandlerBase {
private:
	using CompetitionRepository = infrastructure::repositories::CompetitionRepository;
	std::shared_ptr<CompetitionRepository> competitionRepository;

public:
	static constexpr std::string_view kName = "handler-competitions-id";

	CompetitionsId(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		competitionRepository( component_context.FindComponent<armai::infrastructure::components::CompetitionRepositoryComponent>().GetCompetitionRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		LOG_WARNING() << "CompetitionsId: start";

		auto &response = request.GetHttpResponse();

		if (!utils::auth::checkExistsJwt(request)) {
			response.SetStatus(userver::server::http::HttpStatus::kUnauthorized);
			return {};
		}

		const auto jwt = utils::auth::getJwt(request);
        const auto claims = domain::utils::jwt::decodeJwt(jwt.value());

		const auto competition = competitionRepository->getCompetition(std::stoi(request.GetPathArg(0)));
        if (!competition.has_value()) {
            response.SetStatus(userver::server::http::HttpStatus::kNotFound);
			return {};
        }

        auto competitionQuery = application::mappers::competitions::dto::queryFromDomain(competition.value());
		competitionQuery.isOwner = (competition.value().ownerId == claims.userId);

        response.SetHeader((std::string)"Content-Type", (std::string)"application/json");
        return userver::formats::json::ToString(
            mappers::competitions::json::toJson(competitionQuery)
        );
	}
};

} // namespace

void AppendCompetitionsId(userver::components::ComponentList &component_list) {
	component_list.Append<CompetitionsId>();
}

} // namespace armai::application::handlers
