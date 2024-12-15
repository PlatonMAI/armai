#pragma once

#include <userver/storages/postgres/cluster.hpp>

#include <infrastructure/repositories/participants/participantRepository.hpp>

namespace armai::infrastructure::repositories::participants {

class ParticipantRepositoryPostgres : public ParticipantRepository {
public:
    ParticipantRepositoryPostgres(const userver::storages::postgres::ClusterPtr pg_cluster) : pg_cluster_(pg_cluster) {}

    virtual int registerParticipant(const ParticipantRegisterCommand&, const int competitionId, const int userId) const override final;
    virtual int confirmationParticipant(const int competitionId, const int userId) const override final;
    virtual int weighingParticipant(const ParticipantWeighingCommand&) const override final;

    virtual bool checkRegisterParticipant(const int competitionId, const int userId) const override final;
    virtual bool checkConfirmationParticipant(const int competitionId, const int userId) const override final;

    virtual std::vector<ParticipantAsUser> getUsersRegisteredCompetition(const int competitionId) const override final;
    virtual std::vector<ParticipantAsUser> getUsersConfirmedCompetition(const int competitionId) const override final;

    virtual std::optional<ParticipantAsUser> getWinnerCategory(const int competitionId, const int categoryId) const override final;

    virtual void deleteUsersUnConfirmed(const int competitionId) const override final;

    virtual bool checkEveryoneWeighing(const int competitionId) const override final;

    virtual bool setCategory(const int participantId, const int categoryId) const override final;

    virtual std::vector<int> getParticipantsByTeam(const int) const override final;
    virtual std::optional<Participant> getParticipant(const int) const override final;

private:
    userver::storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace armai::infrastructure::repositories::participants
