#include "view.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/server/http/http_method.hpp>

#include <infrastructure/components/repositories/categorySchemaRepositoryComponent.hpp>
#include <infrastructure/components/repositories/categoryRepositoryComponent.hpp>
#include <application/utils/auth.hpp>
#include <application/utils/categorySchemas.hpp>
#include <domain/utils/jwt.hpp>

namespace armai::application::handlers {
	
namespace {

class CategorySchemas final : public userver::server::handlers::HttpHandlerBase {
private:
	using CategorySchemaRepository = infrastructure::repositories::CategorySchemaRepository;
	std::shared_ptr<CategorySchemaRepository> categorySchemaRepository;
	using CategoryRepository = infrastructure::repositories::CategoryRepository;
	std::shared_ptr<CategoryRepository> categoryRepository;

public:
	static constexpr std::string_view kName = "handler-category_schemas";

	CategorySchemas(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		categorySchemaRepository( component_context.FindComponent<armai::infrastructure::components::CategorySchemaRepositoryComponent>().GetCategorySchemaRepository() ),
		categoryRepository( component_context.FindComponent<armai::infrastructure::components::CategoryRepositoryComponent>().GetCategoryRepository() ) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		LOG_WARNING() << "CategorySchemas: start";

		auto &response = request.GetHttpResponse();

		if (!utils::auth::checkExistsJwt(request)) {
			response.SetStatus(userver::server::http::HttpStatus::kUnauthorized);
			return {};
		}

		const auto jwt = utils::auth::getJwt(request);
        const auto claims = domain::utils::jwt::decodeJwt(jwt.value());

		switch (request.GetMethod()) {
			case userver::server::http::HttpMethod::kPost:
				LOG_WARNING() << "CategorySchemas: kPost";
				response.SetHeader((std::string)"Content-Type", (std::string)"application/json");
				return utils::categorySchemas::createCategorySchema(request, claims.userId, categorySchemaRepository, categoryRepository);
			case userver::server::http::HttpMethod::kGet:
				LOG_WARNING() << "CategorySchemas: kGet";
				response.SetHeader((std::string)"Content-Type", (std::string)"application/json");
				return utils::categorySchemas::getCategorySchemas(categorySchemaRepository);
			default:
				throw userver::server::handlers::ClientError(
					userver::server::handlers::ExternalBody{fmt::format("Unsupported method {}", request.GetMethod())}
				);
		}
	}
};

} // namespace

void AppendCategorySchemas(userver::components::ComponentList &component_list) {
	component_list.Append<CategorySchemas>();
}

} // namespace armai::application::handlers
