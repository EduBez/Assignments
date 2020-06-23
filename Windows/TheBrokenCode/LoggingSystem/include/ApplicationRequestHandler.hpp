#ifndef APPLICATION_REQUEST_HANDLER_HPP_INCLUDED
#define APPLICATION_REQUEST_HANDLER_HPP_INCLUDED

#pragma once

#include "RequestHandler.hpp"

namespace brokencode {
namespace server {
        
class ApplicationRequestHandler final : public RequestHandler {
public:
    explicit ApplicationRequestHandler(const web::http::method &method) : RequestHandler { method } {}
    void Handle(const web::http::http_request &, service::LoggingService *) override;
};
        
}
}

#endif //APPLICATION_REQUEST_HANDLER_HPP_INCLUDED
