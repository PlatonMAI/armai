#include "auth.hpp"

#include <userver/crypto/hash.hpp>

namespace armai::domain::utils::auth {

namespace {
const std::string salt = "YaLubluElenuAleksandrovnuPegachkovu";
}

std::string getHashPassword(const std::string& password) {
    return userver::crypto::hash::Sha256(salt + password);
}

bool verifyPassword(const std::string& password, const std::string& hashPassword) {
    return ( getHashPassword(password) == hashPassword );
}

}
// namespace armai::domain::utils::auth
