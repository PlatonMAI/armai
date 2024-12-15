#pragma once

#include <string>
#include <optional>

namespace armai::application::dto::armfights {

struct ArmfightCreateCommand {
    int competitionId;
    int categoryId;
    std::optional<int> participantFirstId;
    std::optional<int> participantSecondId;
    std::optional<int> armfightFirstId;
    std::optional<int> armfightSecondId;
    std::string hand;
    bool isFinal;
};

} // namespace armai::application::dto::armfights
