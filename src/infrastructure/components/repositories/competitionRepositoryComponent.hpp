#include <memory>

#include <userver/components/component_base.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/postgres/component.hpp>

#include <infrastructure/repositories/competitions/competitionRepositoryPostgres.hpp>

namespace armai::infrastructure::components {

class CompetitionRepositoryComponent : public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "competition-repository-component";

    CompetitionRepositoryComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context
    ) : ComponentBase(config, component_context),
        competition_repository_(std::shared_ptr<repositories::CompetitionRepository>(
            new repositories::competitions::CompetitionRepositoryPostgres(component_context.FindComponent<userver::components::Postgres>("postgres-db").GetCluster())
        )) {}

    std::shared_ptr<repositories::CompetitionRepository> GetCompetitionRepository() const;

private:
    std::shared_ptr<repositories::CompetitionRepository> competition_repository_;
};

} // namespace armai::infrastructure::components
