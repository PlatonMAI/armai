#include <memory>

#include <userver/components/component_base.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/postgres/component.hpp>

#include <infrastructure/repositories/categories/categoryRepositoryPostgres.hpp>

namespace armai::infrastructure::components {

class CategoryRepositoryComponent : public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "category-repository-component";

    CategoryRepositoryComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context
    ) : ComponentBase(config, component_context),
        category_repository_(std::shared_ptr<repositories::CategoryRepository>(
            new repositories::categories::CategoryRepositoryPostgres(component_context.FindComponent<userver::components::Postgres>("postgres-db").GetCluster())
        )) {}

    std::shared_ptr<repositories::CategoryRepository> GetCategoryRepository() const;

private:
    std::shared_ptr<repositories::CategoryRepository> category_repository_;
};

} // namespace armai::infrastructure::components
