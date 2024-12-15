#pragma once

#include <optional>
#include <vector>

#include <domain/participants/participant.hpp>
#include <domain/participants/participantAsUser.hpp>
#include <application/dto/participants/participantRegisterCommand.hpp>
#include <application/dto/participants/participantWeighingCommand.hpp>

namespace armai::infrastructure::repositories {

class ParticipantRepository {
public:
    using Participant = domain::participants::Participant;
    using ParticipantAsUser = domain::participants::ParticipantAsUser;
    using ParticipantRegisterCommand = application::dto::participants::ParticipantRegisterCommand;
    using ParticipantWeighingCommand = application::dto::participants::ParticipantWeighingCommand;

    virtual int registerParticipant(const ParticipantRegisterCommand&, const int competitionId, const int userId) const;
    virtual int confirmationParticipant(const int competitionId, const int userId) const;
    virtual int weighingParticipant(const ParticipantWeighingCommand&) const;

    virtual bool checkRegisterParticipant(const int competitionId, const int userId) const;
    virtual bool checkConfirmationParticipant(const int competitionId, const int userId) const;

    virtual std::vector<ParticipantAsUser> getUsersRegisteredCompetition(const int competitionId) const;
    virtual std::vector<ParticipantAsUser> getUsersConfirmedCompetition(const int competitionId) const;

    virtual std::optional<ParticipantAsUser> getWinnerCategory(const int competitionId, const int categoryId) const;

    virtual void deleteUsersUnConfirmed(const int competitionId) const;

    virtual bool checkEveryoneWeighing(const int competitionId) const;

    virtual bool setCategory(const int participantId, const int categoryId) const;

    virtual std::vector<int> getParticipantsByTeam(const int) const;
    virtual std::optional<Participant> getParticipant(const int) const;
};

} // namespace armai::infrastructure::repositories
