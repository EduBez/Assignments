#include "Constants.hpp"
#include "LoggingService.hpp"
#include "LoggingException.hpp"

namespace brokencode {
namespace service {

using repository::LoggingRepository;
using boost::uuids::random_generator;
using boost::uuids::to_string;
    
LoggingService::LoggingService() : LoggingRepositoryPtr { std::make_unique<LoggingRepository>() } {}
    
std::string& LoggingService::Auth(const std::string &applicationId, const std::string &secret) {
    auto accessToken = constants::EmptyStr;
    model::Application application(applicationId, secret);
    if (LoggingRepositoryPtr->HasApplication(application)) {
        auto uuid = to_string(random_generator()());
        if (LoggingRepositoryPtr->CreateToken(uuid, application)) {
            accessToken = uuid;
        }
        return accessToken;
    }
    throw new exception::InvalidCredentialsException();
}
    
bool LoggingService::Log(const std::string &accessToken, const model::LogItem &logItem) {
    if (LoggingRepositoryPtr->IsAccessTokenValid(accessToken, logItem.GetApplicationId())) {
        return LoggingRepositoryPtr->AddLogItem(logItem);
    }
    throw new exception::InvalidAccessTokenException();
}

model::Application& LoggingService::Register(const std::string &displayName) {
    auto id = to_string(random_generator()());
    auto secret = to_string(random_generator()());
    model::Application application(id, secret, displayName);
    if (LoggingRepositoryPtr->AddApplication(application)) {
        return application;
    }
    throw new exception::RegisterApplicationException();
}
    
std::vector<model::Application> LoggingService::GetApplications(const std::string &userId, const std::string &secret) {
    model::User user(userId, secret);
    if (LoggingRepositoryPtr->HasUser(user)) {
        return LoggingRepositoryPtr->GetApplications();
    }
    throw new exception::InvalidCredentialsException();
}
    
}
}
