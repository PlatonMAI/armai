#pragma once

#include <string_view>
#include <userver/logging/log.hpp>
#include <userver/storages/redis/client.hpp>

namespace armai::infrastructure::repositories::redis {

class RedisRepository {
public:
    RedisRepository(
        userver::storages::redis::ClientPtr redis_client_,
        userver::storages::redis::CommandControl redis_cc_
    ) : redis_client_(redis_client_), redis_cc_(redis_cc_) {
        LOG_ERROR() << redis_client_.get();
    }

    std::optional<std::string> GetValue(std::string_view key);

private:
    userver::storages::redis::ClientPtr redis_client_;
    userver::storages::redis::CommandControl redis_cc_;
};

} // namespace armai::infrastructure::repositories::redis
