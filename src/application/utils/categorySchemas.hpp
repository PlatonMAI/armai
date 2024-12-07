#pragma once

#include <userver/server/http/http_request.hpp>

namespace armai::application::utils::categorySchemas {

std::string createCategorySchema(const userver::server::http::HttpRequest&, const int ownerId);

} // namespace armai::application::utils::categorySchemas
