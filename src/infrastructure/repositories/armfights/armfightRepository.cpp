#include "armfightRepository.hpp"

#include <exception>

namespace armai::infrastructure::repositories {

int ArmfightRepository::createArmfight(const ArmfightCreateCommand&) const {
    throw std::exception();
}

bool ArmfightRepository::winArmfight(const ArmfightWinCommand&) const {
    throw std::exception();
}

std::optional<ArmfightRepository::Armfight> ArmfightRepository::getArmfight(const int, const int) const {
    throw std::exception();
}

} // namespace armai::infrastructure::repositories
