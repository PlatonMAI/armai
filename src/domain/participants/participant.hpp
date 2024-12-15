#pragma once

#include <optional>

namespace armai::domain::participants {

struct Participant {
    int id;
    int userId;
    int competitionId;
    std::optional<int> teamId;
    std::optional<int> weight;
    std::optional<int> age;
};

} // namespace armai::domain::participants
