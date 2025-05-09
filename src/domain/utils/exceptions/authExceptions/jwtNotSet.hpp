#include <domain/utils/exceptions/authExceptions/auth.hpp>

namespace armai::domain::utils::exceptions::auth {

class JwtNotSetException: public AuthException
{
};

} // namespace armai::domain::utils::exceptions::auth
