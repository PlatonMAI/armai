#include "redisRepositoryComponent.hpp"

#include <userver/yaml_config/merge_schemas.hpp>

namespace armai::infrastructure::components {

std::shared_ptr<repositories::redis::RedisRepository> RedisRepositoryComponent::GetRedisRepository() const {
    return redis_repository_;
}

userver::yaml_config::Schema RedisRepositoryComponent::GetStaticConfigSchema() {
    return userver::yaml_config::MergeSchemas<userver::components::ComponentBase>(R"(
type: object
description: user component RedisRepositoryComponent
additionalProperties: false
properties:
    ttl-refresh:
        type: integer
        description: time to live refresh token in redis
)");
}

} // namespace armai::infrastructure::components
