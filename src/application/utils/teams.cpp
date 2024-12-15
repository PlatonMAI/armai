#include "teams.hpp"

#include <userver/formats/json.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/logging/log.hpp>

#include <application/dto/teams/teamMulQuery.hpp>
#include <application/mappers/teams/request.hpp>
#include <application/mappers/teams/dto.hpp>
#include <application/mappers/teams/json.hpp>
#include <domain/teams/team.hpp>

namespace armai::application::utils::teams {

std::string createTeam(
    const userver::server::http::HttpRequest& request, const int ownerId,
    const std::shared_ptr<infrastructure::repositories::TeamRepository> teamRepository
) {
    const auto bodyJson = userver::formats::json::FromString(request.RequestBody());
    const auto teamCreateCommand = mappers::teams::request::getTeamCreateCommand(bodyJson);

    const auto teamId = teamRepository->createTeam(teamCreateCommand, ownerId);

    return userver::formats::json::ToString(
    userver::formats::json::MakeObject(
            "id", teamId
        )
    );
}

std::string getTeams(
    const std::shared_ptr<infrastructure::repositories::TeamRepository> teamRepository
) {
    const auto teams = teamRepository->getTeams();

    std::vector<dto::teams::TeamMulQuery> teamsQuery;
    for (const auto& team : teams) {
        teamsQuery.push_back(mappers::teams::dto::mulQueryFromDomain(team));
    }

    userver::formats::json::ValueBuilder response;
    response["teams"] = userver::formats::json::ValueBuilder{};
    for (const auto& teamQuery : teamsQuery) {
        response["teams"].PushBack(application::mappers::teams::json::toJson(teamQuery));
    }

    return userver::formats::json::ToString(
        response.ExtractValue()
    );
}

} // namespace armai::application::utils::teams
