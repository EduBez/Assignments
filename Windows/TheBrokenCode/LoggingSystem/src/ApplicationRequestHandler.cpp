#include "ApplicationRequestHandler.hpp"
#include "LoggingException.hpp"

namespace brokencode {
namespace server {
    
static void SendJsonResponse(const web::http::http_request &request, std::vector<model::Application> applications) {
    std::vector<web::json::value> apps;
    std::vector<model::Application>::iterator iterator;
    for (iterator = applications.begin(); iterator != applications.end(); iterator++) {
        apps.push_back(web::json::value::object({
                        { "application_id", web::json::value::string(iterator->GetId()) },
                        { "display_name",   web::json::value::string(iterator->GetDisplayName()) }
                      }));
    }
    auto response = web::json::value::array(apps);
    request.reply(web::http::status_codes::OK, response);
}
    
void ApplicationRequestHandler::Handle(const web::http::http_request &request, service::LoggingService *service) {
    try {
        auto headers = request.headers();
        auto valueIt = headers.find("Authorization");
        if ((valueIt == headers.end()) || (valueIt->second.empty())) {
            SendJsonErrorResponse(web::http::status_codes::BadRequest, request, U("Missing authorization header"));
        } else {
            std::vector<std::string> tokens;
            boost::split(tokens, valueIt->second, boost::is_any_of(":"));
            auto applications = service->GetApplications(tokens.at(0), tokens.at(1));
            SendJsonResponse(request, applications);
        }
    } catch (const exception::LoggingException e) {
        SendJsonErrorResponse(web::http::status_codes::OK, request, U("Invalid credentials"));
    }
}
        
}
}
