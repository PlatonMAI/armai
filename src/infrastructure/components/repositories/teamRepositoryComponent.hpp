#include <memory>

#include <userver/components/component_base.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/postgres/component.hpp>

#include <infrastructure/repositories/teams/teamRepositoryPostgres.hpp>

namespace armai::infrastructure::components {

class TeamRepositoryComponent : public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "team-repository-component";

    TeamRepositoryComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context
    ) : ComponentBase(config, component_context),
        team_repository_(std::shared_ptr<repositories::TeamRepository>(
            new repositories::teams::TeamRepositoryPostgres(component_context.FindComponent<userver::components::Postgres>("postgres-db").GetCluster())
        )) {}

    std::shared_ptr<repositories::TeamRepository> GetTeamRepository() const;

private:
    std::shared_ptr<repositories::TeamRepository> team_repository_;
};

} // namespace armai::infrastructure::components
