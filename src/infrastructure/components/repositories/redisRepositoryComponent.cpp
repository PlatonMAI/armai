#include "redisRepositoryComponent.hpp"

namespace armai::infrastructure::components {

std::shared_ptr<repositories::redis::RedisRepository> RedisRepositoryComponent::GetRedisRepository() const {
    return redis_repository_;
}

} // namespace armai::infrastructure::components
