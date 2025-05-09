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
#include <application/dto/categories/categoryQuery.hpp>
#include <application/mappers/competitions/dto.hpp>
#include <application/mappers/competitions/json.hpp>
#include <application/mappers/categories/dto.hpp>
#include <application/mappers/categories/json.hpp>
#include <infrastructure/components/repositories/competitionRepositoryComponent.hpp>
#include <infrastructure/components/repositories/categoryRepositoryComponent.hpp>
#include <infrastructure/components/repositories/redisRepositoryComponent.hpp>
#include <domain/utils/jwt.hpp>
#include <domain/competitions/competitions.hpp>

namespace armai::application::handlers {
	
namespace {

class CompetitionsIdCategories final : public userver::server::handlers::HttpHandlerBase {
private:
	std::shared_ptr<infrastructure::repositories::CompetitionRepository> competitionRepository;
	std::shared_ptr<infrastructure::repositories::CategoryRepository> categoryRepository;
	std::shared_ptr<infrastructure::repositories::redis::RedisRepository> redisRepository;

public:
	static constexpr std::string_view kName = "handler-competitions-id-categories";

	CompetitionsIdCategories(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		competitionRepository( component_context.FindComponent<armai::infrastructure::components::CompetitionRepositoryComponent>().GetCompetitionRepository() ),
		categoryRepository( component_context.FindComponent<armai::infrastructure::components::CategoryRepositoryComponent>().GetCategoryRepository() ),
		redisRepository( component_context.FindComponent<armai::infrastructure::components::RedisRepositoryComponent>().GetRedisRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		auto &response = request.GetHttpResponse();
		utils::auth::checkAuth(request, response, redisRepository);

		const auto competition = competitionRepository->getCompetition(std::stoi(request.GetPathArg(0)));
        if (!competition.has_value()) {
            response.SetStatus(userver::server::http::HttpStatus::kNotFound);
			return {};
        }

		if (competition.value().status != domain::competitions::kInProcess && competition.value().status != domain::competitions::kFinished) {
			response.SetStatus(userver::server::http::HttpStatus::kBadRequest);
			return {};
		}

        const auto categories = categoryRepository->getCategories(competition->categorySchemaId);
		std::vector<dto::categories::CategoryQuery> categoriesQuery;
        for (const auto& category : categories) {
            categoriesQuery.push_back( application::mappers::categories::dto::queryFromDomain(category) );
        }

		userver::formats::json::ValueBuilder responseBodyJson;
		responseBodyJson["categories"] = userver::formats::json::ValueBuilder{};
		for (const auto& category : categoriesQuery) {
            responseBodyJson["categories"].PushBack( mappers::categories::json::toJson(category) );
        }

        response.SetHeader((std::string)"Content-Type", (std::string)"application/json");

        return userver::formats::json::ToString(
            responseBodyJson.ExtractValue()
        );
	}
};

} // namespace

void AppendCompetitionsIdCategories(userver::components::ComponentList &component_list) {
	component_list.Append<CompetitionsIdCategories>();
}

} // namespace armai::application::handlers
