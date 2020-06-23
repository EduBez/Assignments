#ifndef REQUEST_HANDLER_HPP_INCLUDED
#define REQUEST_HANDLER_HPP_INCLUDED

#pragma once

#include "LoggingService.hpp"

namespace brokencode {
namespace server {

using RequestHandlerPtr = std::unique_ptr<class RequestHandler>;
using HandlerMap = std::map<std::string, RequestHandlerPtr>;

class RequestHandler {
public:
    RequestHandler(const web::http::method &method) : Method { method } {}
    virtual void Handle(const web::http::http_request &, service::LoggingService *) = 0;
    const auto GetMethod() const { return Method; }
    static void SendJsonErrorResponse(web::http::status_code status,
                                      const web::http::http_request &request,
                                      std::string &&message) {
        auto response = web::json::value::object({ { "error_message", web::json::value::string(message) } });
        request.reply(status, response);
    }
private:
    const web::http::method Method;
};
    
}
}

#endif //REQUEST_HANDLER_HPP_INCLUDED
