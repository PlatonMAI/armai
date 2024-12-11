#pragma once

#include <userver/server/http/http_request.hpp>

#include <infrastructure/repositories/categorySchemas/categorySchemaRepository.hpp>
#include <infrastructure/repositories/categories/categoryRepository.hpp>

namespace armai::application::utils::categorySchemas {

std::string createCategorySchema(
    const userver::server::http::HttpRequest& request, const int ownerId,
    const std::shared_ptr<infrastructure::repositories::CategorySchemaRepository>,
    const std::shared_ptr<infrastructure::repositories::CategoryRepository>
);

std::string getCategorySchemas(
    const std::shared_ptr<infrastructure::repositories::CategorySchemaRepository> categorySchemaRepository
);

} // namespace armai::application::utils::categorySchemas
