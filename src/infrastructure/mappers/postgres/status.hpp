#pragma once

#include <userver/storages/postgres/io/io_fwd.hpp>
#include <userver/storages/postgres/io/pg_types.hpp>
#include <userver/utils/trivial_map.hpp>

#include <domain/competitions/competitions.hpp>

namespace userver::storages::postgres::io {

template <>
struct CppToUserPg<armai::domain::competitions::Status> {
    static constexpr DBTypeName postgres_name = "public.status_enum";
    static constexpr USERVER_NAMESPACE::utils::TrivialBiMap enumerators = [](auto selector) {
        return selector()
            .Case("registration", armai::domain::competitions::Status::kRegistration)
            .Case("confirmation", armai::domain::competitions::Status::kConfirmation)
            .Case("weighing", armai::domain::competitions::Status::kWeighing)
            .Case("in_process", armai::domain::competitions::Status::kInProcess)
            .Case("finished", armai::domain::competitions::Status::kFinished);
    };
};

} // namespace userver::storages::postgres::io
