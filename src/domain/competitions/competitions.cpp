#include "competitions.hpp"

namespace armai::domain::competitions {

bool checkCorrectCategory(const domain::participants::ParticipantAsUser& participant, const domain::categories::Category category) {
    return
    (!category.sex.has_value() || category.sex.value() == participant.sex) &&
    (!category.ageMin.has_value() || category.ageMin.value() <= participant.age.value()) &&
    (!category.ageMax.has_value() || category.ageMax.value() > participant.age.value()) &&
    (!category.weightMin.has_value() || category.weightMin.value() <= participant.weight.value()) &&
    (!category.weightMax.has_value() || category.weightMax.value() > participant.weight.value());
}

} // namespace armai::domain::competitions
