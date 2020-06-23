#ifndef LOGGING_REPOSITORY_HPP_INCLUDED
#define LOGGING_REPOSITORY_HPP_INCLUDED

#pragma once

#include "Repository.hpp"

namespace brokencode {
namespace model {

class User;
class LogItem;
class Application;

}
}

namespace brokencode {
namespace repository {
    
class LoggingRepository final : public Repository {
public:
    LoggingRepository();
    ~LoggingRepository();
    bool AddLogItem(const model::LogItem &) noexcept;
    bool HasUser(const model::User &) noexcept;
    bool HasApplication(const model::Application &) noexcept;
    bool AddApplication(const model::Application &) noexcept;
    bool CreateToken(const std::string &, const model::Application &) noexcept;
    bool IsAccessTokenValid(const std::string &, const std::string &) noexcept;
    std::vector<model::Application> GetApplications() noexcept;
private:
    class Impl;
    std::auto_ptr<Impl> PImpl;
};
    
}
}

#endif //LOGGING_REPOSITORY_HPP_INCLUDED
