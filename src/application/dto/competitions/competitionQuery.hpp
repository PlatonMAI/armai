#pragma once

#include <string>
#include <optional>

#include <domain/competitions/competitions.hpp>

namespace armai::application::dto::competitions {

struct CompetitionQuery {
    int id;
    std::string name;
    std::optional<domain::competitions::Hand> hand;
    domain::competitions::Status status;
    bool isOwner;
};

} // namespace armai::application::dto::competitions
