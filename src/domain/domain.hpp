#pragma once

#include <string>

#include <userver/utils/datetime/date.hpp>

namespace armai::domain {
    // 29.10.2004
    userver::utils::datetime::Date getDateFromString(const std::string&);
}
