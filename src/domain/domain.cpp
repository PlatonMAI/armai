#include "domain.hpp"
#include <string>

namespace armai::domain {
    userver::utils::datetime::Date getDateFromString(const std::string &src) {
        return userver::utils::datetime::Date(
            std::stoi( std::string(src.begin(), src.begin() + 2) ),
            std::stoi( std::string(src.begin() + 3, src.begin() + 5) ),
            std::stoi( std::string(src.begin() + 6, src.end()) )
        );
    }
}
