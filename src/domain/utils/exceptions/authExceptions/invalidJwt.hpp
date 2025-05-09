#include <domain/utils/exceptions/authExceptions/auth.hpp>

namespace armai::domain::utils::exceptions::auth {

class InvalidJwtException: public AuthException
{
};

} // namespace armai::domain::utils::exceptions::auth
