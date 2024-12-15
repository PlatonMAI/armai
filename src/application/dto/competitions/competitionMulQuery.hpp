#pragma once

#include <string>

#include <domain/competitions/competitions.hpp>

namespace armai::application::dto::competitions {

struct CompetitionMulQuery {
    int id;
    std::string name;
    domain::competitions::Status status;
};

} // namespace armai::application::dto::competitions
