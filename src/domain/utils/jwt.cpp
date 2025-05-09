#include "jwt.hpp"

#include <chrono>

#include <userver/logging/log.hpp>

#include <domain/utils/exceptions/authExceptions/lifetimeExpired.hpp>

namespace armai::domain::utils::jwt {

namespace {
const std::string secret = "YaLubluElenuAleksandrovnuPegachkovu";
const double magicNumber = 4.2222222222;
}

std::string createJwt(const Claims& claims) {
    LOG_WARNING() << "createJwt: start";
    const double d = magicNumber * claims.userId;
    LOG_WARNING() << "createJwt: claims: " << "userid: " << d << ", isAdmin: " << claims.isAdmin;
    const auto token = ::jwt::create()
        .set_type(kType)
        .set_issuer(kIssuer)
        .set_payload_claim(kUserId, ::jwt::claim(picojson::value(d)))
        .set_payload_claim(kIsAdmin, ::jwt::claim(picojson::value(claims.isAdmin)))
        .set_payload_claim(kCreatedAt, ::jwt::claim(picojson::value(claims.createdAt.time_since_epoch().count())))
        .sign(::jwt::algorithm::hs256{secret});

    return token;
}

void verifyJwt(const ::jwt::decoded_jwt<::jwt::traits::kazuho_picojson> jwt, const Claims& claims) {
    LOG_WARNING() << "verifyJwt: start";
    const double d = magicNumber * claims.userId;
    LOG_WARNING() << "verifyJwt: claims: " << "userid: " << d << ", isAdmin: " << claims.isAdmin;

    const auto verifier = ::jwt::verify()
        .with_type(kType)
        .with_issuer(kIssuer)
        .with_claim(kUserId, ::jwt::claim(picojson::value(d)))
        .with_claim(kIsAdmin, ::jwt::claim(picojson::value(claims.isAdmin)))
        .with_claim(kCreatedAt, ::jwt::claim(picojson::value(claims.createdAt.time_since_epoch().count())))
        .allow_algorithm(::jwt::algorithm::hs256{secret});

    verifier.verify(jwt);
}

Claims decodeJwt(const std::string& jwt) {
    const auto decoded = ::jwt::decode(jwt);
    const auto payload = decoded.get_payload_json();

    const Claims claims{
        static_cast<int>(payload.at(kUserId).get<double>() / magicNumber),
        payload.at(kIsAdmin).get<bool>(),
        TimePointMs(std::chrono::milliseconds(payload.at(kCreatedAt).get<long>()))
    };

    verifyJwt(decoded, claims);

    return claims;
}

void verifyTtlJwt(const Claims& claims) {
    const auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    const auto diff = now - claims.createdAt;
    if (diff.count() > kTtlJwt) {
        throw exceptions::auth::LifetimeExpiredException();
    }
}

}
// namespace armai::domain::utils::auth
