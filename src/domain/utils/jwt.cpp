#include "jwt.hpp"
#include <userver/logging/log.hpp>

namespace armai::domain::utils::jwt {

namespace {
const std::string secret = "YaLubluElenuAleksandrovnuPegachkovu";
}

std::string createJwt(const Claims& claims) {
    const double d = 4.2 * claims.userId;
    const auto token = ::jwt::create()
        .set_type(kType)
        .set_issuer(kIssuer)
        .set_payload_claim(kUserId, ::jwt::claim(picojson::value(d)))
        .set_payload_claim(kIsAdmin, ::jwt::claim(picojson::value(claims.isAdmin)))
        .sign(::jwt::algorithm::hs256{secret});

    return token;
}

void verifyJwt(const ::jwt::decoded_jwt<::jwt::traits::kazuho_picojson> jwt, const Claims& claims) {
    const double d = 4.2 * claims.userId;
    const auto verifier = ::jwt::verify()
        .with_type(kType)
        .with_issuer(kIssuer)
        .with_claim(kUserId, ::jwt::claim(picojson::value(d)))
        .with_claim(kIsAdmin, ::jwt::claim(picojson::value(claims.isAdmin)))
        .allow_algorithm(::jwt::algorithm::hs256{secret});

    verifier.verify(jwt);
}

Claims decodeJwt(const std::string& jwt) {
    const auto decoded = ::jwt::decode(jwt);
    const auto payload = decoded.get_payload_json();

    const Claims claims{
        static_cast<int>(payload.at(kUserId).get<double>() / 4.2),
        payload.at(kIsAdmin).get<bool>()
    };

    verifyJwt(decoded, claims);

    return claims;
}

}
// namespace armai::domain::utils::auth
