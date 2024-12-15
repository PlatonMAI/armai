#pragma once

#include <userver/server/http/http_request.hpp>

#include <infrastructure/repositories/competitions/competitionRepository.hpp>
#include <infrastructure/repositories/participants/participantRepository.hpp>
#include <infrastructure/repositories/categories/categoryRepository.hpp>
#include <infrastructure/repositories/armfights/armfightRepository.hpp>
#include <infrastructure/repositories/users/userRepository.hpp>
#include <domain/competitions/competitions.hpp>
#include <domain/participants/participantAsUser.hpp>
#include <domain/categories/category.hpp>
#include <domain/armfights/armfight.hpp>
#include <domain/competitions/competition.hpp>

namespace armai::application::utils::competitions {

std::string createCompetition(
    const userver::server::http::HttpRequest&, const int ownerId,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository>
);

std::string getCompetitions(
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository>
);
std::string getCompetitionsByStatus(
    const userver::server::http::HttpRequest&,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository>
);

std::string changeStatusRegistration(
    const int competitionId,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository>
);
std::string changeStatusConfirmation(
    const int competitionId,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository>,
    const std::shared_ptr<infrastructure::repositories::ParticipantRepository>
);
std::string changeStatusWeighing(
    userver::server::http::HttpResponse&,
    const int competitionId, const std::optional<domain::competitions::Hand> hand,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository>,
    const std::shared_ptr<infrastructure::repositories::ParticipantRepository>,
    const std::shared_ptr<infrastructure::repositories::CategoryRepository>,
    const std::shared_ptr<infrastructure::repositories::ArmfightRepository>
);
std::string changeStatusInProcess(
    const int competitionId,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository>
);

void generateGrid(
    const int categoryId, const std::vector<int>&,
    const int competitionId, const domain::competitions::Hand,
    const std::shared_ptr<infrastructure::repositories::ArmfightRepository>
);

std::string winArmfight(
    userver::server::http::HttpResponse&,
    const userver::server::http::HttpRequest&,
    const std::shared_ptr<infrastructure::repositories::ArmfightRepository>
);

std::string getArmfight(
    userver::server::http::HttpResponse&,
    const userver::server::http::HttpRequest&,
    const std::shared_ptr<infrastructure::repositories::ParticipantRepository>,
    const std::shared_ptr<infrastructure::repositories::UserRepository>,
    const std::shared_ptr<infrastructure::repositories::ArmfightRepository>
);

} // namespace armai::application::utils::competitions
