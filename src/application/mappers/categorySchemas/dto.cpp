#include "dto.hpp"

namespace armai::application::mappers::categorySchemas::dto {

CategorySchemaMulQuery mulQueryFromDomain(const CategorySchemaDomain& schemaDomain) {
    return {
        schemaDomain.id,
        schemaDomain.name
    };
}
CategorySchemaQuery queryFromDomain(const CategorySchemaDomain& schemaDomain) {
    return {
        schemaDomain.id,
        schemaDomain.name,
        {}
    };
}

} // namespace armai::application::mappers::categorySchemas::dto
