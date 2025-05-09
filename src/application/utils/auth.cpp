#include "auth.hpp"

#include <chrono>

#include <exception>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/logging/log.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

#include <application/utils/auth.hpp>
#include <application/mappers/users/request.hpp>
#include <infrastructure/components/repositories/userRepositoryComponent.hpp>
#include <infrastructure/components/repositories/redisRepositoryComponent.hpp>
#include <domain/utils/exceptions/authExceptions/auth.hpp>
#include <domain/utils/exceptions/authExceptions/jwtNotSet.hpp>
#include <domain/utils/exceptions/authExceptions/invalidJwt.hpp>
#include <domain/utils/exceptions/authExceptions/lifetimeExpired.hpp>
#include <domain/utils/exceptions/authExceptions/refreshNotSet.hpp>
#include <domain/utils/exceptions/authExceptions/invalidRefresh.hpp>
#include <domain/utils/auth.hpp>
#include <domain/utils/refresh.hpp>
#include "domain/utils/exceptions/alreadyAuth.hpp"

namespace armai::application::utils::auth {

std::optional<std::string> getToken(const userver::server::http::HttpRequest& request, const std::string& cookieName) {
    const auto token = request.GetCookie(cookieName);
    if (token == "")
        return {};
    return token;
}

userver::server::http::Cookie buildCookieToken(const std::string& cookieName, const std::string& token) {
    userver::server::http::Cookie cookie(cookieName, token);
    cookie.SetHttpOnly();
    cookie.SetPath("/");

    return cookie;
}

void auth(
    const int userId, const bool isAdmin,
    userver::server::http::HttpResponse& response,
    std::shared_ptr<armai::infrastructure::repositories::redis::RedisRepository> redisRepository
) {
    const auto timePoint = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    const auto claims = domain::utils::jwt::Claims{userId, isAdmin, timePoint};
    const auto jwt = domain::utils::jwt::createJwt(claims);
    response.SetCookie(utils::auth::buildCookieToken(utils::auth::kJwtCookieName, jwt));

    const auto refresh = domain::utils::refresh::getRefresh(userId);
    redisRepository->SaveRefresh(userId, refresh);
    response.SetCookie(utils::auth::buildCookieToken(utils::auth::kRefreshCookieName, refresh));
}

domain::utils::jwt::Claims checkAuth(
    const userver::server::http::HttpRequest& request,
    userver::server::http::HttpResponse& response,
    std::shared_ptr<armai::infrastructure::repositories::redis::RedisRepository> redisRepository
) {
    const auto jwt = utils::auth::getToken(request, kJwtCookieName);
    if (!jwt.has_value()) {
        throw domain::utils::exceptions::auth::JwtNotSetException();
    }

    domain::utils::jwt::Claims claims;
    try {
        claims = domain::utils::jwt::decodeJwt(jwt.value());
    } catch (std::exception&) {
        throw domain::utils::exceptions::auth::InvalidJwtException();
    }

    try {
        domain::utils::jwt::verifyTtlJwt(claims);
    } catch (domain::utils::exceptions::auth::LifetimeExpiredException&) {
        const auto refresh = utils::auth::getToken(request, kRefreshCookieName);
        if (!refresh.has_value()) {
            throw domain::utils::exceptions::auth::RefreshNotSetException();
        }

        const auto refreshRedis = redisRepository->GetRefresh(claims.userId);
        if (!refreshRedis.has_value() || refresh.value() != refreshRedis.value()) {
            throw domain::utils::exceptions::auth::InvalidRefreshException();
        }

        redisRepository->DelRefresh(claims.userId);
        auth(claims.userId, claims.isAdmin, response, redisRepository);
    }

    return claims;
}

void checkNotAuth(
    const userver::server::http::HttpRequest& request,
    userver::server::http::HttpResponse& response,
    std::shared_ptr<armai::infrastructure::repositories::redis::RedisRepository> redisRepository
) {
    try {
        utils::auth::checkAuth(request, response, redisRepository);
        throw domain::utils::exceptions::AlreadyAuthException();
    } catch (domain::utils::exceptions::auth::AuthException&) {}
}

} // namespace armai::application::utils::auth
