#pragma once

#include <domain/competitions/competitions.hpp>

namespace armai::application::dto::armfights {

struct ArmfightQuery {
    int id;
    int participantFirstId;
    int participantSecondId;
    domain::competitions::Hand hand;
    std::string participantFirstName;
    std::string participantSecondName;
};

} // namespace armai::application::dto::armfights
