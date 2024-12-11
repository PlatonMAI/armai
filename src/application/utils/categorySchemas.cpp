#include "categorySchemas.hpp"

#include <userver/formats/json.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/logging/log.hpp>

#include <domain/categorySchemas/categorySchemas.hpp>
#include <application/dto/categorySchemas/categorySchemaMulQuery.hpp>
#include <application/dto/categories/categoryCreateCommand.hpp>
#include <application/mappers/categorySchemas/dto.hpp>
#include <application/mappers/categorySchemas/json.hpp>
#include <application/mappers/categories/dto.hpp>

namespace armai::application::utils::categorySchemas {

std::string createCategorySchema(
    const userver::server::http::HttpRequest& request, const int ownerId,
    const std::shared_ptr<infrastructure::repositories::CategorySchemaRepository> categorySchemaRepository,
    const std::shared_ptr<infrastructure::repositories::CategoryRepository> categoryRepository
) {
    const auto requestJson = userver::formats::json::FromString(request.RequestBody());
    const auto schemaName = requestJson[ domain::categorySchemas::kStrFromField.at(domain::categorySchemas::Field::kName) ].As<std::string>();
    
    const auto schemaJson = requestJson[ domain::categorySchemas::kStrFromField.at(domain::categorySchemas::Field::kSchema) ];
    const auto categories = domain::categorySchemas::createCategoriesFromSchemaJson(schemaJson);

    for (const auto& category : categories) {
        LOG_WARNING()
            << "category:\n"
            << "\tsex: " << ( category.sex.has_value() ? domain::users::kStringFromSex.at(category.sex.value()) : "null" ) << "\n"
            << "\tage: " << ( category.ageMin.has_value() ? std::to_string(category.ageMin.value()) : "null" ) << " - " << ( category.ageMax.has_value() ? std::to_string(category.ageMax.value()) : "null" ) << "\n"
            << "\tweight: " << ( category.weightMin.has_value() ? std::to_string(category.weightMin.value()) : "null" ) << " - " << ( category.weightMax.has_value() ? std::to_string(category.weightMax.value()) : "null" ) << "\n";
    }

    const auto schemaId = categorySchemaRepository->createSchema(dto::categorySchemas::CategorySchemaCreateCommand{ schemaName }, ownerId);
    for (auto category : categories) {
        category.schemaId = schemaId;
        categoryRepository->createCategory(mappers::categories::dto::createCommandFromDomain(category));
    }

    return userver::formats::json::ToString(
    userver::formats::json::MakeObject(
            "id", schemaId
        )
    );
}

std::string getCategorySchemas(
    const std::shared_ptr<infrastructure::repositories::CategorySchemaRepository> categorySchemaRepository
) {
    LOG_WARNING() << "getCategorySchemas: запрашиваю схемы";
    const auto categorySchemas = categorySchemaRepository->getSchemas();
    LOG_WARNING() << "getCategorySchemas: получил схемы";

    std::vector<dto::categorySchemas::CategorySchemaMulQuery> categorySchemasQuery;
    for (const auto& categorySchema : categorySchemas) {
        categorySchemasQuery.push_back(mappers::categorySchemas::dto::mulQueryFromDomain(categorySchema));
    }
    LOG_WARNING() << "getCategorySchemas: смапил схемы в запрос";

    userver::formats::json::ValueBuilder response;
    response["schemas"] = userver::formats::json::ValueBuilder{};
    for (const auto& categorySchema : categorySchemasQuery) {
        response["schemas"].PushBack(application::mappers::categorySchemas::json::toJson(categorySchema));
    }
    LOG_WARNING() << "getCategorySchemas: построил json";

    return userver::formats::json::ToString(
        response.ExtractValue()
    );
}

} // namespace armai::application::utils::categorySchemas
