#pragma once

#include <application/dto/armfights/armfightCreateCommand.hpp>
#include <application/dto/armfights/armfightWinCommand.hpp>
#include <domain/armfights/armfight.hpp>

namespace armai::infrastructure::repositories {

class ArmfightRepository {
public:
    using Armfight = domain::armfights::Armfight;
    using ArmfightCreateCommand = application::dto::armfights::ArmfightCreateCommand;
    using ArmfightWinCommand = application::dto::armfights::ArmfightWinCommand;

    virtual int createArmfight(const ArmfightCreateCommand&) const;

    virtual bool winArmfight(const ArmfightWinCommand&) const;

    virtual std::optional<Armfight> getArmfight(const int competitionId, const int categoryId) const;
};

} // namespace armai::infrastructure::repositories
