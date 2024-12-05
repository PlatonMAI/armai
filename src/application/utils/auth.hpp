#pragma once

#include <userver/server/http/http_request.hpp>

namespace armai::application::utils::auth {

const std::string kJwtCookieName = "access_token";

bool checkExistsJwt(const userver::server::http::HttpRequest&);
std::optional<std::string> getJwt(const userver::server::http::HttpRequest&);

userver::server::http::Cookie buildCookieJwt(const std::string&);

} // namespace armai::application::utils::auth
