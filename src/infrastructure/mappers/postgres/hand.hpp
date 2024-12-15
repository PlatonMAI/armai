#pragma once

#include <userver/storages/postgres/io/io_fwd.hpp>
#include <userver/storages/postgres/io/pg_types.hpp>
#include <userver/utils/trivial_map.hpp>

#include <domain/competitions/competitions.hpp>

namespace userver::storages::postgres::io {

template <>
struct CppToUserPg<armai::domain::competitions::Hand> {
    static constexpr DBTypeName postgres_name = "public.hand_enum";
    static constexpr USERVER_NAMESPACE::utils::TrivialBiMap enumerators = [](auto selector) {
        return selector()
            .Case("left", armai::domain::competitions::Hand::kLeft)
            .Case("right", armai::domain::competitions::Hand::kRight);
    };
};

} // namespace userver::storages::postgres::io
