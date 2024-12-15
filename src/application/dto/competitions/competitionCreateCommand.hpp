#pragma once

#include <string>
#include <optional>

#include <domain/competitions/competitions.hpp>

namespace armai::application::dto::competitions {

struct CompetitionCreateCommand {
    std::string name;
    std::optional<std::string> hand;
    int categorySchemaId;
};

} // namespace armai::application::dto::competitions
