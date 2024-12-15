#pragma once

#include <userver/server/http/http_request.hpp>

#include <infrastructure/repositories/teams/teamRepository.hpp>

namespace armai::application::utils::teams {

std::string createTeam(
    const userver::server::http::HttpRequest& request, const int ownerId,
    const std::shared_ptr<infrastructure::repositories::TeamRepository>
);

std::string getTeams(
    const std::shared_ptr<infrastructure::repositories::TeamRepository>
);

} // namespace armai::application::utils::teams
