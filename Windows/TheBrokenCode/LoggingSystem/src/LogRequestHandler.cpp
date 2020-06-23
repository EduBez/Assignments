#include "LogRequestHandler.hpp"
#include "Model.hpp"

#include "LoggingException.hpp"

namespace brokencode {
namespace server {
    
static void SendJsonResponse(const std::string &accessToken,
                             const web::json::value &json,
                             const web::http::http_request &request,
                             brokencode::service::LoggingService *service) {
    auto object = json.as_object();
    model::LogItem logItem(object[U("level")].as_string(),
                           object[U("logger")].as_string(),
                           object[U("message")].as_string(),
                           object[U("application_id")].as_string());
    auto result = service->Log(accessToken, logItem);
    auto response = web::json::value::object({ { "success", web::json::value::boolean(result) } });
    request.reply(web::http::status_codes::OK, response);
}
    
void LogRequestHandler::Handle(const web::http::http_request &request, service::LoggingService *service) {
    try {
        auto json = request.extract_json().get();
        auto headers = request.headers();
        auto valueIt = headers.find("Authorization");
        if ((valueIt == headers.end()) || (valueIt->second.empty())) {
            SendJsonErrorResponse(web::http::status_codes::BadRequest, request, U("Missing authorization header"));
        } else if (json.is_null()) {
            SendJsonErrorResponse(web::http::status_codes::BadRequest, request, U("Missing json request"));
        } else {
            SendJsonResponse(valueIt->second, json, request, service);
        }
    } catch (const exception::InvalidAccessTokenException &e) {
        SendJsonErrorResponse(web::http::status_codes::OK, request, U("Invalid access token"));
    } 
}
    
}
}
