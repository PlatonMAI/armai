#pragma once

#include <optional>

#include <domain/competitions/competitions.hpp>

namespace armai::domain::armfights {

struct Armfight {
    std::optional<int> id;
    int competitionId;
    int categoryId;
    std::optional<int> participantFirstId;
    std::optional<int> participantSecondId;
    std::optional<int> armfightFirstId;
    std::optional<int> armfightSecondId;
    competitions::Hand hand;
    std::optional<int> winnerId;
};

} // namespace armai::domain::armfights
