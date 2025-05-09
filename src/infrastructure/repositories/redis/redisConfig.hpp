#pragma once

#include <userver/yaml_config/yaml_config.hpp>

namespace armai::infrastructure::repositories::redis {

struct RedisConfig {
    std::chrono::milliseconds ttlRefresh;
};

RedisConfig Parse(const userver::yaml_config::YamlConfig& yaml, userver::formats::parse::To<RedisConfig>);

} // namespace armai::infrastructure::repositories::redis
