#pragma once

#include <string>
#include <vector>

#include <domain/teams/participant.hpp>

namespace armai::application::dto::teams {

struct TeamQuery {
    int id;
    std::string name;
    int winsArmfights;
    int winsCompetitions;
    std::vector<domain::teams::Participant> participants;
};

} // namespace armai::application::dto::teams
