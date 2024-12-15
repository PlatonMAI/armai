#pragma once

#include <string>
#include <unordered_map>
#include <optional>

namespace armai::domain::users {

enum Sex { kMale, kFemale };
const std::unordered_map<std::string, Sex> kSexFromString{
    {"male", kMale},
    {"female", kFemale}
};
const std::unordered_map<Sex, std::string> kStringFromSex{
    {kMale, "male"},
    {kFemale, "female"}
};
const std::unordered_map<std::optional<Sex>, std::optional<std::string>> kStringOptionalFromSex{
    {std::nullopt, std::nullopt},
    {kMale, "male"},
    {kFemale, "female"}
};

} // namespace armai::domain::users
