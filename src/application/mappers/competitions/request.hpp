#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/competitions/competitionCreateCommand.hpp>

namespace armai::application::mappers::competitions::request {

using CompetitionCreateCommand = application::dto::competitions::CompetitionCreateCommand;

CompetitionCreateCommand getCompetitionCreateCommand(const userver::formats::json::Value&);

} // namespace armai::application::mappers::competitions::request
