#include "parameterStore.hpp"

#include <userver/storages/postgres/io/date.hpp>

namespace armai::infrastructure::mappers::users::parameterStore {

userver::storages::postgres::ParameterStore toStore(const application::dto::users::UserRegisterCommand& user) {
    userver::storages::postgres::ParameterStore parameters;
    parameters.PushBack(user.email);
    parameters.PushBack(user.password);
    parameters.PushBack(user.name);
    parameters.PushBack(user.sex);
    parameters.PushBack(user.birth);

    return parameters;
}

} // namespace armai::infrastructure::mappers::users::parameterStore
