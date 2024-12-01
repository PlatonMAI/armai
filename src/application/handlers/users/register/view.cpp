#include "view.hpp"

#include <fmt/format.h>
#include <iostream>

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/formats/json.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>

#include <jwt-cpp/jwt.h>

namespace armai {
	
namespace {

class UsersRegister final : public userver::server::handlers::HttpHandlerBase {
private:
	userver::storages::postgres::ClusterPtr pg_cluster_;

public:
	static constexpr std::string_view kName = "handler-users-register";

	UsersRegister(
		const userver::components::ComponentConfig& config,
		const userver::components::ComponentContext& component_context
	) : HttpHandlerBase(config, component_context),
		pg_cluster_(component_context.FindComponent<userver::components::Postgres>("postgres-db").GetCluster()) {}

	std::string HandleRequestThrow(
		const userver::server::http::HttpRequest &request,
		userver::server::request::RequestContext &
	) const override {
		const auto bodyJson = userver::formats::json::FromString(request.RequestBody());

		return bodyJson["name"].As<std::string>();
	}
};

} // namespace

void AppendUsersRegister(userver::components::ComponentList &component_list) {
	component_list.Append<UsersRegister>();
}

} // namespace armai
