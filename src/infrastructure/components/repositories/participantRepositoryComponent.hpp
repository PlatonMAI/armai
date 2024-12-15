#include <memory>

#include <userver/components/component_base.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/postgres/component.hpp>

#include <infrastructure/repositories/participants/participantRepositoryPostgres.hpp>

namespace armai::infrastructure::components {

class ParticipantRepositoryComponent : public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "participant-repository-component";

    ParticipantRepositoryComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context
    ) : ComponentBase(config, component_context),
        participant_repository_(std::shared_ptr<repositories::ParticipantRepository>(
            new repositories::participants::ParticipantRepositoryPostgres(component_context.FindComponent<userver::components::Postgres>("postgres-db").GetCluster())
        )) {}

    std::shared_ptr<repositories::ParticipantRepository> GetParticipantRepository() const;

private:
    std::shared_ptr<repositories::ParticipantRepository> participant_repository_;
};

} // namespace armai::infrastructure::components
