#include <memory>

#include <userver/components/component_base.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/postgres/component.hpp>

#include <infrastructure/repositories/users/userRepositoryPostgres.hpp>

namespace armai::infrastructure::components {

class UserRepositoryComponent : public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "user-repository-component";

    UserRepositoryComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context
    ) : ComponentBase(config, component_context),
        user_repository_(std::shared_ptr<repositories::UserRepository>(
            new repositories::users::UserRepositoryPostgres(component_context.FindComponent<userver::components::Postgres>("postgres-db").GetCluster())
        )) {}

    std::shared_ptr<repositories::UserRepository> GetUserRepository() const;

private:
    std::shared_ptr<repositories::UserRepository> user_repository_;
};

} // namespace armai::infrastructure::components
