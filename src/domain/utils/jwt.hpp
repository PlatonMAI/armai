#pragma once

#include <string>

#include <jwt-cpp/jwt.h>

namespace armai::domain::utils::jwt {

const std::string kType = "JWT";
const std::string kIssuer = "armai";
const std::string kUserId = "id";
const std::string kIsAdmin = "admin";

struct Claims {
    int userId;
    bool isAdmin;
};

std::string createJwt(const Claims&);
void verifyJwt(const ::jwt::decoded_jwt<::jwt::traits::kazuho_picojson>, const Claims&);
Claims decodeJwt(const std::string&);

}
// namespace armai::domain::utils::auth
