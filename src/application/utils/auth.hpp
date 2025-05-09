#pragma once

#include <userver/server/http/http_request.hpp>
#include <userver/server/http/http_response.hpp>

#include <infrastructure/repositories/redis/redisRepository.hpp>
#include <domain/utils/jwt.hpp>

namespace armai::application::utils::auth {

const std::string kJwtCookieName = "access_token";
const std::string kRefreshCookieName = "refresh_token";

std::optional<std::string> getToken(const userver::server::http::HttpRequest&, const std::string& cookieName);

userver::server::http::Cookie buildCookieToken(const std::string& cookieName, const std::string& token);

void auth(
    const int userId, const bool isAdmin,
    userver::server::http::HttpResponse&,
    std::shared_ptr<armai::infrastructure::repositories::redis::RedisRepository>
);

domain::utils::jwt::Claims checkAuth(
    const userver::server::http::HttpRequest&,
    userver::server::http::HttpResponse&,
    std::shared_ptr<armai::infrastructure::repositories::redis::RedisRepository>
);

void checkNotAuth(
    const userver::server::http::HttpRequest&,
    userver::server::http::HttpResponse&,
    std::shared_ptr<armai::infrastructure::repositories::redis::RedisRepository>
);

} // namespace armai::application::utils::auth
