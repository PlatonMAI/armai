#pragma once

#include <string>

namespace armai::domain::teams {

struct Team {
    int id;
    int ownerId;
    std::string name;
    int winsArmfights;
    int winsCompetitions;
};

} // namespace armai::domain::teams
