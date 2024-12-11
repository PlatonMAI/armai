#pragma once

#include <vector>
#include <unordered_map>

#include <userver/formats/json/value.hpp>

#include <domain/categories/category.hpp>
#include <domain/categorySchemas/categorySchema.hpp>

namespace armai::domain::categorySchemas {

using Category = domain::categories::Category;

enum Field { kName, kSchema, kSex, kAge, kWeight };
const std::unordered_map<Field, std::string> kStrFromField{
    {kName, "name"},
    {kSchema, "schema"},
    {kSex, "sex"},
    {kAge, "age"},
    {kWeight, "weight"}
};
const std::unordered_map<std::string, Field> kFieldFromStr{
    {"name", kName},
    {"schema", kSchema},
    {"sex", kSex},
    {"age", kAge},
    {"weight", kWeight}
};

void parseSchemaJson(
    const std::optional<users::Sex> sex,
    const std::optional<int> ageMin,
    const std::optional<int> ageMax,
    const std::optional<int> weightMin,
    const std::optional<int> weightMax,
    const userver::formats::json::Value& schemaJson,
    std::vector<Category>& categories
);
std::vector<Category> createCategoriesFromSchemaJson(const userver::formats::json::Value&);

} // namespace armai::domain::categorySchemas
