#include "auth.hpp"

namespace armai::application::utils::auth {

bool checkExistsJwt(const userver::server::http::HttpRequest& request) {
    const auto cookies = request.GetCookieNames();
    return (std::find(cookies.begin(), cookies.end(), kJwtCookieName) != cookies.end());
}

std::optional<std::string> getJwt(const userver::server::http::HttpRequest& request) {
    if (!checkExistsJwt(request))
        return {};

    return request.GetCookie(kJwtCookieName);
}

userver::server::http::Cookie buildCookieJwt(const std::string& jwt) {
    userver::server::http::Cookie cookie(utils::auth::kJwtCookieName, jwt);
    cookie.SetHttpOnly();
    cookie.SetPath("/");

    return cookie;
}

} // namespace armai::application::utils::auth
