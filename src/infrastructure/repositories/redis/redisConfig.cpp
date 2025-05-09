#include "redisConfig.hpp"

namespace armai::infrastructure::repositories::redis {

RedisConfig Parse(const userver::yaml_config::YamlConfig& yaml, userver::formats::parse::To<RedisConfig>) {
    return RedisConfig{std::chrono::milliseconds(yaml["ttl-refresh"].As<long>())};
}

} // namespace armai::infrastructure::repositories::redis
