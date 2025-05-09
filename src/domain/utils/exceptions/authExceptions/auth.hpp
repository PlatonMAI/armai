#pragma once

#include <userver/server/handlers/exceptions.hpp>

namespace armai::domain::utils::exceptions::auth {

class AuthException: public userver::server::handlers::CustomHandlerException
{
public:
    AuthException()
        : CustomHandlerException(userver::server::handlers::HandlerErrorCode::kUnauthorized) {}
};

} // namespace armai::domain::utils::exceptions::auth
