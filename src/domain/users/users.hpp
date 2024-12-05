#pragma once

#include <string>
#include <unordered_map>

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
}
