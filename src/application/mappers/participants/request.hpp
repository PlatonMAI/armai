#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/participants/participantRegisterCommand.hpp>
#include <application/dto/participants/participantWeighingCommand.hpp>

namespace armai::application::mappers::participants::request {

using ParticipantRegisterCommand = application::dto::participants::ParticipantRegisterCommand;
using ParticipantWeighingCommand = application::dto::participants::ParticipantWeighingCommand;

ParticipantRegisterCommand getParticipantRegisterCommand(const userver::formats::json::Value&);
ParticipantWeighingCommand getParticipantWeighingCommand(const userver::formats::json::Value&);

} // namespace armai::application::mappers::participants::request
