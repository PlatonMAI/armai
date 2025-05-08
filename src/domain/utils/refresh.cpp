#include "refresh.hpp"

namespace armai::domain::utils::refresh {

namespace {
const std::string salt = "YaLubluElenuAleksandrovnuPegachkovu";
}

std::string getRefresh(const int userId) {
    return userver::crypto::hash::Sha256(salt + std::to_string(userId));
};

}
// namespace armai::domain::utils::auth
