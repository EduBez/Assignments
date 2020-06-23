#ifndef LOGGING_SERVICE_HPP_INCLUDED
#define LOGGING_SERVICE_HPP_INCLUDED

#pragma once

using namespace std;

#include "Model.hpp"
#include "Application.hpp"
#include "LoggingRepository.hpp"

namespace brokencode {
namespace service {
    
typedef std::unique_ptr<repository::LoggingRepository> LoggingRepositoryPtr;
    
class LoggingService final {
public:
    LoggingService();
    string& Auth(const string &, const string &);
    model::Application& Register(const string &);
    std::vector<model::Application> GetApplications(const string &, const string &);
    bool Log(const string &, const model::LogItem &);
private:
    LoggingRepositoryPtr LoggingRepositoryPtr;
};

}
}

#endif //LOGGING_SERVICE_HPP_INCLUDED
