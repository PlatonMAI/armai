#pragma once

#include <optional>

namespace armai::application::dto::participants {

struct ParticipantRegisterCommand {
    std::optional<int> teamId;
};

} // namespace armai::application::dto::participants
