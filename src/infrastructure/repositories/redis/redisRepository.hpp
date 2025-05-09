#pragma once

#include <string_view>
#include <userver/logging/log.hpp>
#include <userver/storages/redis/client.hpp>

#include <infrastructure/repositories/redis/redisConfig.hpp>

namespace armai::infrastructure::repositories::redis {

class RedisRepository {
public:
    RedisRepository(
        userver::storages::redis::ClientPtr redis_client_,
        userver::storages::redis::CommandControl redis_cc_,
        RedisConfig config_
    ) : redis_client_(redis_client_), redis_cc_(redis_cc_), config_(config_) {}

    std::optional<std::string> GetValue(std::string_view key);

    void SaveRefresh(const int userId, const std::string& refresh);
    std::optional<std::string> GetRefresh(const int userId);
    void DelRefresh(const int userId);

private:
    userver::storages::redis::ClientPtr redis_client_;
    userver::storages::redis::CommandControl redis_cc_;
    RedisConfig config_;

    std::string BuildRefreshKey(const int userId);
};

} // namespace armai::infrastructure::repositories::redis
