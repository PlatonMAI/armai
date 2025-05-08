#include "redisRepository.hpp"

namespace armai::infrastructure::repositories::redis {

std::optional<std::string> RedisRepository::GetValue(std::string_view key) {
    const auto result = redis_client_->Get(std::string{key}, redis_cc_).Get();
    if (!result)
        return {};
    
    return *result;
}
    
} // namespace armai::infrastructure::repositories::redis
