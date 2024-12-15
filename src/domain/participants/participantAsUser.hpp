#pragma once

#include <optional>
#include <string>

#include <domain/users/users.hpp>

namespace armai::domain::participants {

struct ParticipantAsUser {
    int participantId;
    int userId;
    std::string name;
    std::optional<int> teamId;
    std::optional<std::string> teamName;
    std::optional<int> weight;
    std::optional<int> age;
    domain::users::Sex sex;
};

} // namespace armai::domain::participants
