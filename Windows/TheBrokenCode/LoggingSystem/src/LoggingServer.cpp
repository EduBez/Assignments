#include "LoggingServer.hpp"
#include "RequestHandlerFactory.hpp"

namespace brokencode {
namespace server {
    
using web::http::uri;
using web::http::status_codes;
using service::LoggingService;
    
LoggingServer::LoggingServer(utility::string_t url)
    : Listener { url },
      LoggingServicePtr { std::make_unique<LoggingService>() },
      HandlerMap { RequestHandlerFactory::CreateHandlers() } {
    Listener.support(web::http::methods::GET, [this](auto request) {
        HandleRequest(web::http::methods::GET, request);
    });
    Listener.support(web::http::methods::POST, [this](auto request) {
        HandleRequest(web::http::methods::POST, request);
    });
}

void LoggingServer::Start() {
    Listener.open().wait();
}
    
void LoggingServer::Stop() {
    Listener.close().wait();
}

void LoggingServer::HandleRequest(const web::http::method &method, web::http::http_request &request) {
    auto uri = request.relative_uri();
    auto path = uri.path();
    auto value = HandlerMap.find(path);
    if (value == HandlerMap.end()) {
        RequestHandler::SendJsonErrorResponse(status_codes::Forbidden, request, U("Invalid request"));
    } else {
        try {
            auto handler = value->second.get();
            if (handler->GetMethod() == method) {
                handler->Handle(request, LoggingServicePtr.get());
            } else {
                RequestHandler::SendJsonErrorResponse(status_codes::Forbidden, request, U("Request does not supportted"));
            }        
        } catch (const std::exception &e) {
            RequestHandler::SendJsonErrorResponse(status_codes::OK, request, U(e.what()));
        } 
    }
}

}
}
