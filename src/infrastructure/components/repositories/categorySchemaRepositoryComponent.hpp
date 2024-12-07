#include <memory>

#include <userver/components/component_base.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/postgres/component.hpp>

#include <infrastructure/repositories/categorySchemas/categorySchemaRepositoryPostgres.hpp>

namespace armai::infrastructure::components {

class CategorySchemaRepositoryComponent : public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "category-schema-repository-component";

    CategorySchemaRepositoryComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context
    ) : ComponentBase(config, component_context),
        category_schema_repository_(std::shared_ptr<repositories::CategorySchemaRepository>(
            new repositories::categorySchemas::CategorySchemaRepositoryPostgres(component_context.FindComponent<userver::components::Postgres>("postgres-db").GetCluster())
        )) {}

    std::shared_ptr<repositories::CategorySchemaRepository> GetCategorySchemaRepository() const;

private:
    std::shared_ptr<repositories::CategorySchemaRepository> category_schema_repository_;
};

} // namespace armai::infrastructure::components
