#include "armfightRepositoryComponent.hpp"

namespace armai::infrastructure::components {

std::shared_ptr<repositories::ArmfightRepository> ArmfightRepositoryComponent::GetArmfightRepository() const {
    return armfight_repository_;
}

} // namespace armai::infrastructure::components
