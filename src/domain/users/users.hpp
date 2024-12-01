#pragma once

#include <string>
#include <unordered_map>

namespace armai::domain::users {
    enum kSex { MALE, FEMALE };
    const std::unordered_map<std::string, kSex> kSexFromString{
        {"male", MALE},
        {"female", FEMALE}
    };
}
