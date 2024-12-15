#include "competitions.hpp"

#include <unordered_map>

#include <userver/formats/json.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/logging/log.hpp>

#include <application/dto/competitions/competitionMulQuery.hpp>
#include <application/dto/armfights/armfightCreateCommand.hpp>
#include <application/mappers/armfights/dto.hpp>
#include <application/mappers/armfights/json.hpp>
#include <application/mappers/armfights/request.hpp>
#include <application/mappers/competitions/request.hpp>
#include <application/mappers/competitions/dto.hpp>
#include <application/mappers/competitions/json.hpp>
#include <domain/competitions/competition.hpp>
#include <domain/competitions/competitions.hpp>
#include <userver/server/http/http_response.hpp>

namespace armai::application::utils::competitions {

std::string createCompetition(
    const userver::server::http::HttpRequest& request, const int ownerId,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository> competitionRepository
) {
    const auto bodyJson = userver::formats::json::FromString(request.RequestBody());
    const auto competitionCreateCommand = mappers::competitions::request::getCompetitionCreateCommand(bodyJson);

    const auto competitionId = competitionRepository->createCompetition(competitionCreateCommand, ownerId);

    return userver::formats::json::ToString(
    userver::formats::json::MakeObject(
            "id", competitionId
        )
    );
}

std::string getCompetitions(
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository> competitionRepository
) {
    const auto competitions = competitionRepository->getCompetitions();

    std::vector<dto::competitions::CompetitionMulQuery> competitionsQuery;
    for (const auto& competition : competitions) {
        competitionsQuery.push_back(mappers::competitions::dto::mulQueryFromDomain(competition));
    }

    userver::formats::json::ValueBuilder response;
    response["competitions"] = userver::formats::json::ValueBuilder{};
    for (const auto& competitionQuery : competitionsQuery) {
        response["competitions"].PushBack(application::mappers::competitions::json::toJson(competitionQuery));
    }

    return userver::formats::json::ToString(
        response.ExtractValue()
    );
}
std::string getCompetitionsByStatus(
    const userver::server::http::HttpRequest& request,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository> competitionRepository
) {
    const auto status = domain::competitions::kStatusFromString.at(request.GetArg("status"));
    const auto competitions = competitionRepository->getCompetitionsByStatus(status);

    std::vector<dto::competitions::CompetitionMulQuery> competitionsQuery;
    for (const auto& competition : competitions) {
        competitionsQuery.push_back(mappers::competitions::dto::mulQueryFromDomain(competition));
    }

    userver::formats::json::ValueBuilder response;
    response["competitions"] = userver::formats::json::ValueBuilder{};
    for (const auto& competitionQuery : competitionsQuery) {
        response["competitions"].PushBack(application::mappers::competitions::json::toJson(competitionQuery));
    }

    return userver::formats::json::ToString(
        response.ExtractValue()
    );
}


std::string changeStatusRegistration(
    const int competitionId,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository> competitionRepository
) {
    competitionRepository->changeStatus(competitionId, domain::competitions::kConfirmation);

    return {};
}

std::string changeStatusConfirmation(
    const int competitionId,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository> competitionRepository,
    const std::shared_ptr<infrastructure::repositories::ParticipantRepository> participantRepository
) {
    participantRepository->deleteUsersUnConfirmed(competitionId);
    competitionRepository->changeStatus(competitionId, domain::competitions::kWeighing);

    return {};
}

std::string changeStatusWeighing(
    userver::server::http::HttpResponse& response,
    const int competitionId, const std::optional<domain::competitions::Hand> hand,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository> competitionRepository,
    const std::shared_ptr<infrastructure::repositories::ParticipantRepository> participantRepository,
    const std::shared_ptr<infrastructure::repositories::CategoryRepository> categoryRepository,
    const std::shared_ptr<infrastructure::repositories::ArmfightRepository> armfightRepository
) {
    const auto isEveryoneWeighing = participantRepository->checkEveryoneWeighing(competitionId);
    if (!isEveryoneWeighing) {
        response.SetStatus(userver::server::http::HttpStatus::kBadRequest);
        return {};
    }

    competitionRepository->changeStatus(competitionId, domain::competitions::kInProcess);

    const auto categories = categoryRepository->getCategoriesByCompetition(competitionId);
    const auto participants = participantRepository->getUsersConfirmedCompetition(competitionId);

    std::unordered_map<int, std::vector<int>> participantsByCategories;
    for (const auto& participant : participants) {
        for (const auto& category : categories) {
            if (domain::competitions::checkCorrectCategory(participant, category)) {
                participantRepository->setCategory(participant.participantId, category.id.value());
                participantsByCategories[category.id.value()].push_back(participant.participantId);
                break;
            }
        }
    }

    for (const auto& elem : participantsByCategories) {
        if (hand.has_value()) {
            generateGrid(
                elem.first, elem.second,
                competitionId, hand.value(),
                armfightRepository
            );
        } else {
            generateGrid(
                elem.first, elem.second,
                competitionId, domain::competitions::kLeft,
                armfightRepository
            );
            generateGrid(
                elem.first, elem.second,
                competitionId, domain::competitions::kRight,
                armfightRepository
            );
        }
    }

    return {};
}

std::string changeStatusInProcess(
    const int competitionId,
    const std::shared_ptr<infrastructure::repositories::CompetitionRepository>
) {
    return {};
}

void generateGrid(
    const int categoryId, const std::vector<int>& participants,
    const int competitionId, const domain::competitions::Hand hand,
    const std::shared_ptr<infrastructure::repositories::ArmfightRepository> armfightRepository
) {
    std::vector<int> pow2(11);
    pow2[0] = 1;
    for (int i = 1; i <= 10; ++i)
        pow2[i] = pow2[i - 1] * 2;

    int size = participants.size();
    int curPow2 = 1024;
    int l = 0;

    while (size < curPow2) curPow2 /= 2;

    std::vector<int> armfights;
    for (int i = 0; i < curPow2; i += 2) {
        armfights.push_back(armfightRepository->createArmfight({
            competitionId,
            categoryId,
            participants[i],
            participants[i + 1],
            std::nullopt,
            std::nullopt,
            domain::competitions::kStringFromHand.at(hand),
            (size == 2)
        }));
    }
    l = curPow2;
    curPow2 /= 2;

    for (; curPow2 >= 2; curPow2 /= 2) {
        LOG_WARNING() << "curPow2: " << curPow2;
        LOG_WARNING() << "armfights.size: " << armfights.size();
        
        std::vector<int> armfightsNew;
        for (int i = 0; i < curPow2; i += 2) {
            armfightsNew.push_back(armfightRepository->createArmfight({
                competitionId,
                categoryId,
                std::nullopt,
                std::nullopt,
                armfights[i],
                armfights[i + 1],
                domain::competitions::kStringFromHand.at(hand),
                (curPow2 == 2 && l == size)
            }));
        }

        int remainingSize = size - l;
        if (remainingSize >= curPow2) {
            for (int i = l; i < l + curPow2; i += 2) {
                armfightsNew.push_back(armfightRepository->createArmfight({
                    competitionId,
                    categoryId,
                    participants[i],
                    participants[i + 1],
                    std::nullopt,
                    std::nullopt,
                    domain::competitions::kStringFromHand.at(hand),
                    false
                }));
            }

            l += curPow2;
            curPow2 *= 2;
        }

        armfights = armfightsNew;
    }

    if (l != size) {
        armfightRepository->createArmfight({
            competitionId,
            categoryId,
            participants[l],
            std::nullopt,
            std::nullopt,
            armfights[0],
            domain::competitions::kStringFromHand.at(hand),
            true
        });
    }
}

std::string winArmfight(
    userver::server::http::HttpResponse& response,
    const userver::server::http::HttpRequest& request,
    const std::shared_ptr<infrastructure::repositories::ArmfightRepository> armfightRepository
) {
    const auto bodyJson = userver::formats::json::FromString(request.RequestBody());
    const auto armfightWinCommand = mappers::armfights::request::getArmfightWinCommand(bodyJson);

    const auto success = armfightRepository->winArmfight(armfightWinCommand);
    if (!success) {
        response.SetStatus(userver::server::http::HttpStatus::kNotFound);
        return {};
    }

    return {};
}

std::string getArmfight(
    userver::server::http::HttpResponse& response,
    const userver::server::http::HttpRequest& request,
    const std::shared_ptr<infrastructure::repositories::ParticipantRepository> participantRepository,
    const std::shared_ptr<infrastructure::repositories::UserRepository> userRepository,
    const std::shared_ptr<infrastructure::repositories::ArmfightRepository> armfightRepository
) {
    const auto competitionId = std::stoi(request.GetPathArg(0));
    const auto categoryId = std::stoi(request.GetPathArg(1));

    const auto armfight = armfightRepository->getArmfight(competitionId, categoryId);
    if (!armfight.has_value()) {
        response.SetStatus(userver::server::http::HttpStatus::kNotFound);
        return {};
    }

    auto armfightQuery = mappers::armfights::dto::queryFromDomain(armfight.value());
    
    const auto participantFirst = participantRepository->getParticipant(armfightQuery.participantFirstId);
    const auto participantSecond = participantRepository->getParticipant(armfightQuery.participantSecondId);
    const auto userFirst = userRepository->getUserById(participantFirst->userId);
    const auto userSecond = userRepository->getUserById(participantSecond->userId);

    armfightQuery.participantFirstName = userFirst.value().name;
    armfightQuery.participantSecondName = userSecond.value().name;

    return userver::formats::json::ToString(
        mappers::armfights::json::toJson(armfightQuery)
    );
}

} // namespace armai::application::utils::competitions
