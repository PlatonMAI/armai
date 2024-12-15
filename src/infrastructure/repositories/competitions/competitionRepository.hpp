#pragma once

#include <optional>
#include <vector>

#include <domain/competitions/competitions.hpp>
#include <domain/competitions/competition.hpp>
#include <application/dto/competitions/competitionCreateCommand.hpp>

namespace armai::infrastructure::repositories {

class CompetitionRepository {
public:
    using Competition = domain::competitions::Competition;
    using CompetitionCreateCommand = application::dto::competitions::CompetitionCreateCommand;

    using Hand = domain::competitions::Hand;
    using Status = domain::competitions::Status;

    virtual int createCompetition(const CompetitionCreateCommand&, const int ownerId) const;

    virtual std::vector<Competition> getCompetitions() const;
    virtual std::vector<Competition> getCompetitionsByStatus(const Status) const;
    virtual std::optional<Competition> getCompetition(const int) const;

    virtual bool changeStatus(const int, const Status) const;
};

} // namespace armai::infrastructure::repositories
