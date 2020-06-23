#include "Constants.hpp"
#include "RequestHandlerFactory.hpp"
#include "LogRequestHandler.hpp"
#include "AuthRequestHandler.hpp"
#include "RegisterRequestHandler.hpp"
#include "ApplicationRequestHandler.hpp"

namespace brokencode {
namespace server {
        
HandlerMap RequestHandlerFactory::CreateHandlers() {
    HandlerMap map;
    map[constants::LogRequest] = std::make_unique<LogRequestHandler>(web::http::methods::POST);
    map[constants::AuthRequest] = std::make_unique<AuthRequestHandler>(web::http::methods::POST);
    map[constants::RegisterRequest] = std::make_unique<RegisterRequestHandler>(web::http::methods::POST);
    map[constants::ApplicationRequest] = std::make_unique<ApplicationRequestHandler>(web::http::methods::GET);
    return map;
}
        
}
}
