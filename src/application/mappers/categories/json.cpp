#include "json.hpp"

#include <userver/formats/serialize/common_containers.hpp>
#include <userver/formats/json/value_builder.hpp>

#include <domain/users/users.hpp>

namespace armai::application::mappers::categories::json {

userver::formats::json::Value toJson(const CategoryQuery& category) {
    userver::formats::json::ValueBuilder categoryJson;
    categoryJson["sex"] = domain::users::kStringOptionalFromSex.at(category.sex);
    categoryJson["ageMin"] = category.ageMin;
    categoryJson["ageMax"] = category.ageMax;
    categoryJson["weightMin"] = category.weightMin;
    categoryJson["weightMax"] = category.weightMax;
    
    return categoryJson.ExtractValue();
}

} // namespace armai::application::mappers::categories::json
