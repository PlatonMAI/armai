#include "userRepositoryComponent.hpp"

namespace armai::infrastructure::components {

std::shared_ptr<repositories::UserRepository> UserRepositoryComponent::GetUserRepository() const {
    return user_repository_;
}

} // namespace armai::infrastructure::components
