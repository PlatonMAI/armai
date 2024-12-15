#include <memory>

#include <userver/components/component_base.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/postgres/component.hpp>

#include <infrastructure/repositories/armfights/armfightRepositoryPostgres.hpp>

namespace armai::infrastructure::components {

class ArmfightRepositoryComponent : public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "armfight-repository-component";

    ArmfightRepositoryComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context
    ) : ComponentBase(config, component_context),
        armfight_repository_(std::shared_ptr<repositories::ArmfightRepository>(
            new repositories::armfights::ArmfightRepositoryPostgres(component_context.FindComponent<userver::components::Postgres>("postgres-db").GetCluster())
        )) {}

    std::shared_ptr<repositories::ArmfightRepository> GetArmfightRepository() const;

private:
    std::shared_ptr<repositories::ArmfightRepository> armfight_repository_;
};

} // namespace armai::infrastructure::components
