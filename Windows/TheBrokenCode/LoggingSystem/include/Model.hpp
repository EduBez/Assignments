#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#pragma once

using namespace std;

#include "LoggingSystem.hpp"

namespace brokencode {
namespace model {
    
class User {
public:
    User(string id, string secret) : Id { id }, Secret { secret } {}
    const auto GetId() const { return Id; }
    const auto GetSecret() const { return Secret; }
private:
    string Id;
    string Secret;
};

class Application final : public User {
public:
    Application(string id, string secret) : Application { id, secret, "" } {}
    Application(string id, string secret, std::string displayName) : User { id, secret },
    DisplayName { displayName } {}
    const auto GetDisplayName() const { return DisplayName; }
private:
    string DisplayName;
};

class LogItem final {
public:
    LogItem(string level, string logger, string message, string applicationId)
        : Level { level },
          Logger { logger },
          Message { message },
          ApplicationId { applicationId } {}
    const auto GetLevel() const { return Level; }
    const auto GetLogger() const { return Logger; }
    const auto GetMessage() const { return Message; }
    const auto GetApplicationId() const { return ApplicationId; }
private:
    string Level;
    string Logger;
    string Message;
    string ApplicationId;
};

}
}

#endif //MODEL_HPP_INCLUDED

