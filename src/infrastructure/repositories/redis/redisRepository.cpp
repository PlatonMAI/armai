#include "redisRepository.hpp"

#include <userver/logging/log.hpp>

#include <domain/utils/exceptions/notFound.hpp>

namespace armai::infrastructure::repositories::redis {

std::optional<std::string> RedisRepository::GetValue(std::string_view key) {
    const auto result = redis_client_->Get(std::string{key}, redis_cc_).Get();
    if (!result)
        return {};

    return *result;
}

std::string RedisRepository::BuildRefreshKey(const int userId) {
    return "refresh:" + std::to_string(userId);
}

void RedisRepository::SaveRefresh(const int userId, const std::string& refresh) {
    LOG_WARNING() << "ttl-refersh: " << config_.ttlRefresh.count();
    const auto key = BuildRefreshKey(userId);
    auto result = redis_client_->Set(key, refresh, config_.ttlRefresh, redis_cc_);
    result.Wait();
}

std::optional<std::string> RedisRepository::GetRefresh(const int userId) {
    const auto key = BuildRefreshKey(userId);
    auto result = redis_client_->Get(key, redis_cc_);
    return result.Get();
}

void RedisRepository::DelRefresh(const int userId) {
    const auto key = BuildRefreshKey(userId);
    auto result = redis_client_->Del(key, redis_cc_);
    const auto count = result.Get();
    if (count == 0) {
        throw domain::utils::exceptions::NotFoundException();
    }
}
    
} // namespace armai::infrastructure::repositories::redis
