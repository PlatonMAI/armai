#pragma once

#include <userver/formats/json/value.hpp>

#include <application/dto/armfights/armfightWinCommand.hpp>

namespace armai::application::mappers::armfights::request {

using ArmfightWinCommand = application::dto::armfights::ArmfightWinCommand;

ArmfightWinCommand getArmfightWinCommand(const userver::formats::json::Value&);

} // namespace armai::application::mappers::armfights::request
