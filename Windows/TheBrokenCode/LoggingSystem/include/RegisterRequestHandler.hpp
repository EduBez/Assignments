#ifndef REGISTER_REQUEST_HANDLER_HPP_INCLUDED
#define REGISTER_REQUEST_HANDLER_HPP_INCLUDED

#pragma once

#include "RequestHandler.hpp"

namespace brokencode {
namespace server {
        
class RegisterRequestHandler final : public RequestHandler {
public:
    explicit RegisterRequestHandler(const web::http::method &method) : RequestHandler { method } {}
    void Handle(const web::http::http_request &, service::LoggingService *) override;
};
        
}
}

#endif //REGISTER_REQUEST_HANDLER_HPP_INCLUDED
