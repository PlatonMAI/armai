#pragma once

#include <optional>
#include <vector>

#include <domain/teams/team.hpp>
#include <application/dto/teams/teamCreateCommand.hpp>

namespace armai::infrastructure::repositories {

class TeamRepository {
public:
    using Team = domain::teams::Team;
    using TeamCreateCommand = application::dto::teams::TeamCreateCommand;

    virtual int createTeam(const TeamCreateCommand&, const int ownerId) const;

    virtual std::vector<Team> getTeams() const;
    virtual std::optional<Team> getTeam(const int) const;
};

} // namespace armai::infrastructure::repositories
