#ifndef LOG_REQUEST_HANDLER_HPP_INCLUDED
#define LOG_REQUEST_HANDLER_HPP_INCLUDED

#pragma once

#include "RequestHandler.hpp"

namespace brokencode {
namespace server {
        
class LogRequestHandler final : public RequestHandler {
public:
    explicit LogRequestHandler(const web::http::method &method) : RequestHandler { method } {}
    void Handle(const web::http::http_request &, service::LoggingService *) override;
};
        
}
}

#endif //LOG_REQUEST_HANDLER_HPP_INCLUDED
