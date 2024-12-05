#pragma once

#include <userver/storages/postgres/io/io_fwd.hpp>
#include <userver/storages/postgres/io/pg_types.hpp>
#include <userver/utils/trivial_map.hpp>

#include <domain/users/users.hpp>

namespace userver::storages::postgres::io {

template <>
struct CppToUserPg<armai::domain::users::Sex> {
    static constexpr DBTypeName postgres_name = "public.sex_enum";
    static constexpr USERVER_NAMESPACE::utils::TrivialBiMap enumerators = [](auto selector) {
        return selector()
            .Case("male", armai::domain::users::Sex::kMale)
            .Case("female", armai::domain::users::Sex::kFemale);
    };
};

} // namespace userver::storages::postgres::io
