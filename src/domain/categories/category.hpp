#pragma once

#include <optional>

#include <domain/users/users.hpp>

namespace armai::domain::categories {

struct Category {
    std::optional<int> id;
    std::optional<int> schemaId;
    
    std::optional<users::Sex> sex;
    std::optional<int> ageMin;
    std::optional<int> ageMax;
    std::optional<int> weightMin;
    std::optional<int> weightMax;
};

} // namespace armai::domain::categories
