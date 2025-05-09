#include <domain/utils/exceptions/authExceptions/auth.hpp>

namespace armai::domain::utils::exceptions::auth {

class LifetimeExpiredException: public AuthException
{
};

} // namespace armai::domain::utils::exceptions::auth
