#include "AuthRequestHandler.hpp"
#include "LoggingException.hpp"

namespace brokencode {
namespace server {
    
void AuthRequestHandler::Handle(const web::http::http_request &request, service::LoggingService *service) {
    try {
        auto headers = request.headers();
        auto valueIt = headers.find("Authorization");
        if ((valueIt == headers.end()) || (valueIt->second.empty())) {
            SendJsonErrorResponse(web::http::status_codes::BadRequest, request, U("Missing authorization header"));
        } else {
            std::vector<std::string> tokens;
            boost::split(tokens, valueIt->second, boost::is_any_of(":"));
            if (tokens.size() == 2) {    // applicationId:secret
                auto accessToken = service->Auth(tokens.front(), tokens.back());
                auto response = web::json::value::object({ { "access_token", web::json::value::string(accessToken) } });
                request.reply(web::http::status_codes::OK, response);
            } else {
                SendJsonErrorResponse(web::http::status_codes::BadRequest, request, U("Invalid authorization"));
            }
        }
    } catch (const exception::InvalidCredentialsException &e) {
        SendJsonErrorResponse(web::http::status_codes::OK, request, U("Invalid credentials"));
    }
}
        
}
}
