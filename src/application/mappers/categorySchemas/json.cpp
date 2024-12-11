#include "json.hpp"

#include <userver/formats/json/inline.hpp>
#include <userver/formats/json/value_builder.hpp>

#include <application/mappers/categories/json.hpp>

namespace armai::application::mappers::categorySchemas::json {

userver::formats::json::Value toJson(const CategorySchemaMulQuery& schema) {
    return userver::formats::json::MakeObject(
        "id", schema.id,
        "name", schema.name
    );
}

userver::formats::json::Value toJson(const CategorySchemaQuery& schema) {
    userver::formats::json::ValueBuilder schemaJson;
    schemaJson["id"] = schema.id;
    schemaJson["name"] = schema.name;

    schemaJson["categories"] = userver::formats::json::ValueBuilder{};
    for (const auto& category : schema.categories) {
        schemaJson["categories"].PushBack(categories::json::toJson(category));
    }
    
    return schemaJson.ExtractValue();
}

} // namespace armai::application::mappers::categorySchemas::json
