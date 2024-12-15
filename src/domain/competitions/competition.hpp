#pragma once

#include <string>
#include <optional>

#include <domain/competitions/competitions.hpp>

namespace armai::domain::competitions {

struct Competition {
    int id;
    int ownerId;
    std::string name;
    std::optional<Hand> hand;
    int categorySchemaId;
    Status status;
};

} // namespace armai::domain::competitions
