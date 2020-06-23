#ifndef AUTH_REQUEST_HANDLER_HPP_INCLUDED
#define AUTH_REQUEST_HANDLER_HPP_INCLUDED

#pragma once

#include "RequestHandler.hpp"

namespace brokencode {
namespace server {
        
class AuthRequestHandler final : public RequestHandler {
public:
    explicit AuthRequestHandler(const web::http::method &method) : RequestHandler { method } {}
    void Handle(const web::http::http_request &, service::LoggingService *) override;
};
        
}
}

#endif //AUTH_REQUEST_HANDLER_HPP_INCLUDED
