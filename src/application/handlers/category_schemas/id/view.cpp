#include "view.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/server/http/http_method.hpp>

#include <application/utils/auth.hpp>
#include <application/utils/categorySchemas.hpp>
#include <application/mappers/categorySchemas/dto.hpp>
#include <application/mappers/categorySchemas/json.hpp>
#include <application/mappers/categories/dto.hpp>
#include <infrastructure/components/repositories/categorySchemaRepositoryComponent.hpp>
#include <infrastructure/components/repositories/categoryRepositoryComponent.hpp>
#include <domain/utils/jwt.hpp>

namespace armai::application::handlers {
	
namespace {

class CategorySchemasId final : public userver::server::handlers::HttpHandlerBase {
private:
	using CategorySchemaRepository = infrastructure::repositories::CategorySchemaRepository;
	std::shared_ptr<CategorySchemaRepository> categorySchemaRepository;
	using CategoryRepository = infrastructure::repositories::CategoryRepository;
	std::shared_ptr<CategoryRepository> categoryRepository;

public:
	static constexpr std::string_view kName = "handler-category_schemas-id";

	CategorySchemasId(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		categorySchemaRepository( component_context.FindComponent<armai::infrastructure::components::CategorySchemaRepositoryComponent>().GetCategorySchemaRepository() ),
		categoryRepository( component_context.FindComponent<armai::infrastructure::components::CategoryRepositoryComponent>().GetCategoryRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		LOG_WARNING() << "CategorySchemasId: start";

		auto &response = request.GetHttpResponse();

		if (!utils::auth::checkExistsJwt(request)) {
			response.SetStatus(userver::server::http::HttpStatus::kUnauthorized);
			return {};
		}

		const auto jwt = utils::auth::getJwt(request);
        domain::utils::jwt::decodeJwt(jwt.value());

		const auto schema = categorySchemaRepository->getSchema(std::stoi(request.GetPathArg(0)));
        if (!schema.has_value()) {
            response.SetStatus(userver::server::http::HttpStatus::kNotFound);
			return {};
        }

        auto schemaQuery = application::mappers::categorySchemas::dto::queryFromDomain(schema.value());

        const auto categories = categoryRepository->getCategories(schemaQuery.id);
        for (const auto& category : categories) {
            schemaQuery.categories.push_back( application::mappers::categories::dto::queryFromDomain(category) );
        }

        response.SetHeader((std::string)"Content-Type", (std::string)"application/json");

        return userver::formats::json::ToString(
            mappers::categorySchemas::json::toJson(schemaQuery)
        );
	}
};

} // namespace

void AppendCategorySchemasId(userver::components::ComponentList &component_list) {
	component_list.Append<CategorySchemasId>();
}

} // namespace armai::application::handlers
