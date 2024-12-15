#pragma once

#include <optional>
#include <string>
#include <vector>
#include <unordered_map>

#include <domain/categories/category.hpp>
#include <domain/participants/participantAsUser.hpp>

namespace armai::domain::competitions {

enum Hand { kLeft, kRight };
const std::unordered_map<std::string, Hand> kHandFromString{
    {"left", kLeft},
    {"right", kRight}
};
const std::unordered_map<Hand, std::string> kStringFromHand{
    {kLeft, "left"},
    {kRight, "right"}
};
const std::unordered_map<std::optional<Hand>, std::optional<std::string>> kStringOptionalFromHand{
    {std::nullopt, std::nullopt},
    {kLeft, "left"},
    {kRight, "right"}
};

enum Status { kRegistration, kConfirmation, kWeighing, kInProcess, kFinished };
const std::unordered_map<std::string, Status> kStatusFromString{
    {"registration", kRegistration},
    {"confirmation", kConfirmation},
    {"weighing", kWeighing},
    {"inProcess", kInProcess},
    {"finished", kFinished}
};
const std::unordered_map<Status, std::string> kStringFromStatus{
    {kRegistration, "registration"},
    {kConfirmation, "confirmation"},
    {kWeighing, "weighing"},
    {kInProcess, "inProcess"},
    {kFinished, "finished"}
};

bool checkCorrectCategory(const participants::ParticipantAsUser&, const categories::Category);

} // namespace armai::domain::competitions
