#include <userver/components/component_base.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/redis/component.hpp>

#include <infrastructure/repositories/redis/redisConfig.hpp>
#include <infrastructure/repositories/redis/redisRepository.hpp>

namespace armai::infrastructure::components {

class RedisRepositoryComponent : public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "redis-repository-component";

    RedisRepositoryComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context
    ) : ComponentBase(config, component_context),
        redis_repository_(std::shared_ptr<repositories::redis::RedisRepository>(
            new repositories::redis::RedisRepository(
                component_context.FindComponent<userver::components::Redis>("key-value-database").GetClient("db_armai"),
                userver::storages::redis::CommandControl(std::chrono::seconds{15}, std::chrono::seconds{60}, 4),
                config.As<armai::infrastructure::repositories::redis::RedisConfig>()
            )
        )) {}

    std::shared_ptr<repositories::redis::RedisRepository> GetRedisRepository() const;

    static userver::yaml_config::Schema GetStaticConfigSchema();

private:
    std::shared_ptr<repositories::redis::RedisRepository> redis_repository_;
};

} // namespace armai::infrastructure::components
