#include "categorySchemas.hpp"

#include <optional>

#include <userver/formats/json.hpp>
#include <userver/formats/json/exception.hpp>

#include <domain/users/users.hpp>

namespace armai::domain::categorySchemas {

void parseSchemaJson(
    const std::optional<users::Sex> sex,
    const std::optional<int> ageMin,
    const std::optional<int> ageMax,
    const std::optional<int> weightMin,
    const std::optional<int> weightMax,
    const userver::formats::json::Value& schemaJson,
    std::vector<Category>& categories
) {
    std::optional<Field> currentLevel;
    std::optional<int> valuePrev;
    for (const auto& elemSchemaJson : schemaJson) {
        if (elemSchemaJson.HasMember(kStrFromField.at(Field::kSex))) {
            
            if (currentLevel.has_value() && currentLevel != kSex)
                throw userver::formats::json::SchemaValidationException("На одном уровне вложенности с полом оказалось другое поле", {}, {});
            if (sex.has_value())
                throw userver::formats::json::SchemaValidationException("Обнаружено повтороное определение пола", {}, {});
            currentLevel = kSex;

            const auto sex = domain::users::kSexFromString.at(elemSchemaJson[kStrFromField.at(Field::kSex)].As<std::string>());
            const auto childSchemaJson = elemSchemaJson[kStrFromField.at(Field::kSchema)];
            parseSchemaJson(sex, ageMin, ageMax, weightMin, weightMax, childSchemaJson, categories);

        } else if (elemSchemaJson.HasMember(kStrFromField.at(Field::kAge))) {
            
            if (currentLevel.has_value() && currentLevel != kAge)
                throw userver::formats::json::SchemaValidationException("На одном уровне вложенности с возрастом оказалось другое поле", {}, {});
            currentLevel = kAge;

            std::optional<int> ageMaxNew;
            if (!elemSchemaJson[kStrFromField.at(Field::kAge)].IsNull()) {
                if (ageMin.has_value() || ageMax.has_value())
                    throw userver::formats::json::SchemaValidationException("Обнаружено повтороное определение возраста", {}, {});
                ageMaxNew = elemSchemaJson[kStrFromField.at(Field::kAge)].As<int>();
            }

            if (!valuePrev.has_value() && !ageMaxNew.has_value())
                throw userver::formats::json::SchemaValidationException("Обе границы возраста заданы null", {}, {});
            const auto childSchemaJson = elemSchemaJson[kStrFromField.at(Field::kSchema)];
            parseSchemaJson(sex, valuePrev, ageMaxNew, weightMin, weightMax, childSchemaJson, categories);
            
            valuePrev = ageMaxNew;

        } else if (elemSchemaJson.HasMember(kStrFromField.at(Field::kWeight))) {
            
            if (currentLevel.has_value() && currentLevel != kWeight)
                throw userver::formats::json::SchemaValidationException("На одном уровне вложенности с весом оказалось другое поле", {}, {});
            currentLevel = kWeight;
            
            std::optional<int> weightMaxNew;
            if (!elemSchemaJson[kStrFromField.at(Field::kWeight)].IsNull()) {
                weightMaxNew = elemSchemaJson[kStrFromField.at(Field::kWeight)].As<int>();
                if (weightMin.has_value() || weightMax.has_value())
                    throw userver::formats::json::SchemaValidationException("Обнаружено повтороное определение веса", {}, {});
            }

            if (!valuePrev.has_value() && !weightMaxNew.has_value())
                throw userver::formats::json::SchemaValidationException("Обе границы веса заданы null", {}, {});
            const auto childSchemaJson = elemSchemaJson[kStrFromField.at(Field::kSchema)];
            parseSchemaJson(sex, ageMin, ageMax, valuePrev, weightMaxNew, childSchemaJson, categories);

            valuePrev = weightMaxNew;

        } else {

            throw userver::formats::json::SchemaValidationException("Неизвестный ключ", {}, {});

        }
    }

    // Нет текущего уровня = получили пустой список = дошли до конца = пора записывать категорию
    if (!currentLevel.has_value()) {
        // Проверка на соответствие границ
        if (
            (ageMin.has_value() && ageMax.has_value() && ageMin >= ageMax) ||
            (weightMin.has_value() && weightMax.has_value() && weightMin >= weightMax)
        )
            throw userver::formats::json::SchemaValidationException("Несоответствие границ (мЕньшее число идет после бОльшего)", {}, {});

        categories.push_back({
            std::nullopt,
            std::nullopt,
            std::nullopt,

            sex,
            ageMin,
            ageMax,
            weightMin,
            weightMax
        });
    }
}

std::vector<Category> createCategoriesFromSchemaJson(const userver::formats::json::Value& schemaJson) {
    std::vector<Category> categories;
    parseSchemaJson(
        std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        schemaJson, categories
    );
    return categories;
}

} // namespace armai::domain::categorySchemas
