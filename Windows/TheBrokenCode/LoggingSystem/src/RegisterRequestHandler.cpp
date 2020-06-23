#include "RegisterRequestHandler.hpp"
#include "LoggingException.hpp"

namespace brokencode {
namespace server {
    
static void SendJsonResponse(const web::json::value &json,
                             const web::http::http_request &request,
                             brokencode::service::LoggingService *service) {
    auto object = json.as_object();
    auto displaName = object[U("display_name")].as_string();
    auto application = service->Register(displaName);
    auto response = web::json::value::object({
                        { "application_id",     web::json::value::string(application.GetId()) },
                        { "application_secret", web::json::value::string(application.GetSecret()) },
                        { "display_name",       web::json::value::string(application.GetDisplayName()) }
                    });
    request.reply(web::http::status_codes::OK, response);
}
    
void RegisterRequestHandler::Handle(const web::http::http_request &request, service::LoggingService *service) {
    try {
        auto json = request.extract_json().get();
        if (json.is_null()) {
            SendJsonErrorResponse(web::http::status_codes::BadRequest, request, U("Missing json request"));
        } else {
            SendJsonResponse(json, request, service);
        }
    } catch (const exception::RegisterApplicationException &e) {
        SendJsonErrorResponse(web::http::status_codes::OK, request, U("Register application has failed"));
    } 
}
    
}
}
