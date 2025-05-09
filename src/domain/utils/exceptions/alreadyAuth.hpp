#pragma once

#include <userver/server/handlers/exceptions.hpp>

namespace armai::domain::utils::exceptions {

class AlreadyAuthException: public userver::server::handlers::CustomHandlerException
{
public:
    AlreadyAuthException()
        : CustomHandlerException(userver::server::handlers::HandlerErrorCode::kForbidden) {}
};

} // namespace armai::domain::utils::exceptions
