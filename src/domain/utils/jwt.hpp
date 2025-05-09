#pragma once

#include <string>
#include <chrono>

#include <jwt-cpp/jwt.h>

namespace armai::domain::utils::jwt {

const std::string kType = "JWT";
const std::string kIssuer = "armai";
const std::string kUserId = "id";
const std::string kIsAdmin = "admin";
const std::string kCreatedAt = "createdAt";

const int kTtlJwt = 1000 * 60 * 60; // час

using TimePointMs = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>;
struct Claims {
    int userId;
    bool isAdmin;
    TimePointMs createdAt;
};

std::string createJwt(const Claims&);
void verifyJwt(const ::jwt::decoded_jwt<::jwt::traits::kazuho_picojson>, const Claims&);
Claims decodeJwt(const std::string&);
void verifyTtlJwt(const Claims&);

}
// namespace armai::domain::utils::auth
