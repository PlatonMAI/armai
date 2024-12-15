#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/teams/teamCreateCommand.hpp>

namespace armai::application::mappers::teams::request {

using TeamCreateCommand = application::dto::teams::TeamCreateCommand;

TeamCreateCommand getTeamCreateCommand(const userver::formats::json::Value&);

} // namespace armai::application::mappers::teams::request
