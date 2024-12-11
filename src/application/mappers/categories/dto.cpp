#include "dto.hpp"

namespace armai::application::mappers::categories::dto {

CategoryCreateCommand createCommandFromDomain(const CategoryDomain& categoryDomain) {
    return {
        categoryDomain.schemaId.value(),
        categoryDomain.sex,
        categoryDomain.ageMin,
        categoryDomain.ageMax,
        categoryDomain.weightMin,
        categoryDomain.weightMax
    };
}

CategoryQuery queryFromDomain(const CategoryDomain& categoryDomain) {
    return {
        categoryDomain.sex,
        categoryDomain.ageMin,
        categoryDomain.ageMax,
        categoryDomain.weightMin,
        categoryDomain.weightMax
    };
}

} // namespace armai::application::mappers::categories::dto
