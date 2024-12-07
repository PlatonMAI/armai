#include "categorySchemas.hpp"

#include <userver/formats/json.hpp>

#include <domain/categorySchemas/categorySchemas.hpp>
#include <userver/logging/log.hpp>
#include <domain/users/users.hpp>

namespace armai::application::utils::categorySchemas {

std::string createCategorySchema(const userver::server::http::HttpRequest& request, const int ownerId) {
    const auto schemaJson = userver::formats::json::FromString(request.RequestBody());
    const auto categories = domain::categorySchemas::createCategoriesFromSchemaJson(schemaJson);

    for (const auto& category : categories) {
        LOG_WARNING()
            << "category:\n"
            << "\tsex: " << ( category.sex.has_value() ? domain::users::kStringFromSex.at(category.sex.value()) : "null" ) << "\n"
            << "\tage: " << ( category.ageMin.has_value() ? std::to_string(category.ageMin.value()) : "null" ) << " - " << ( category.ageMax.has_value() ? std::to_string(category.ageMax.value()) : "null" ) << "\n"
            << "\tweight: " << ( category.weightMin.has_value() ? std::to_string(category.weightMin.value()) : "null" ) << " - " << ( category.weightMax.has_value() ? std::to_string(category.weightMax.value()) : "null" ) << "\n";
    }

    return {};
}

} // namespace armai::application::utils::categorySchemas
