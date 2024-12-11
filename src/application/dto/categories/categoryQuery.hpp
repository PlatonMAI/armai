#pragma once

#include <optional>

#include <domain/users/users.hpp>

namespace armai::application::dto::categories {

struct CategoryQuery {
    std::optional<domain::users::Sex> sex;
    std::optional<int> ageMin;
    std::optional<int> ageMax;
    std::optional<int> weightMin;
    std::optional<int> weightMax;
};

} // namespace armai::application::dto::categories
