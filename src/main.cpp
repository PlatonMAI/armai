#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/server/handlers/http_handler_static.hpp>
#include <userver/server/handlers/log_level.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include "hello.hpp"

#include <application/handlers/appendHandlers.hpp>
#include <infrastructure/components/repositories/appendRepositories.hpp>

int main(int argc, char* argv[]) {
  auto component_list = userver::components::MinimalServerComponentList()
                            .Append<userver::server::handlers::Ping>()
                            .Append<userver::components::TestsuiteSupport>()
                            .Append<userver::components::HttpClient>()
                            .Append<userver::clients::dns::Component>()
                            .Append<userver::server::handlers::TestsControl>()
                            .Append<userver::components::Postgres>("postgres-db")
                            .Append<userver::components::FsCache>("fs-cache-component")
                            .Append<userver::server::handlers::HttpHandlerStatic>()
                            .Append<userver::server::handlers::LogLevel>();

  armai::AppendHello(component_list);
  
  armai::application::handlers::AppendHandlers(component_list);

  armai::infrastructure::components::AppendRepositories(component_list);

  return userver::utils::DaemonMain(argc, argv, component_list);
}
