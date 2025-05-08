#pragma once

#include <string>
#include <userver/crypto/hash.hpp>

namespace armai::domain::utils::refresh {

std::string getRefresh(const int userId);

}
// namespace armai::domain::utils::auth
