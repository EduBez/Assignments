#ifndef LOGGING_SERVER_HPP_INCLUDED
#define LOGGING_SERVER_HPP_INCLUDED

#pragma once

#include "RequestHandler.hpp"
#include "LoggingService.hpp"

namespace brokencode {
namespace server {
    
typedef std::unique_ptr<service::LoggingService> LoggingServicePtr;
        
class LoggingServer final {
public:
    explicit LoggingServer(utility::string_t);
    void Start();
    void Stop();
private:
    void HandleRequest(const web::http::method &, web::http::http_request &);
    web::http::experimental::listener::http_listener Listener;
    const LoggingServicePtr LoggingServicePtr;
    const HandlerMap HandlerMap;
};
    
}
}

#endif //LOGGING_SERVER_HPP_INCLUDED
