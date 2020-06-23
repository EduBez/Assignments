#include "Constants.hpp"

namespace brokencode {
namespace constants {
        
const std::string LogRequest         { "/log" };
const std::string AuthRequest        { "/auth" };
const std::string RegisterRequest    { "/register" };
const std::string ApplicationRequest { "/application" };
const std::string EmptyStr           { "" };
const std::string DatabaseKey        { "BrokenCode" };
const std::string InsertTok          { "INSERT INTO token(access_token, application_id, status) VALUES ((?), (?), 1)" };
const std::string UpdateTok          { "UPDATE token SET status = 0 where application_id = (?)" };
const std::string InsertLog          { "INSERT INTO log(application_id, logger, level, message) VALUES ((?), (?), (?), (?))" };
const std::string InsertApp          { "INSERT INTO application(application_id, display_name, secret) VALUES ((?), (?), (?))" };
const std::string SelectUser         { "SELECT * FROM user WHERE user_id = (?) and secret = (?)" };
const std::string SelectApp          { "SELECT * FROM application WHERE application_id = (?) and secret = (?)" };
const std::string SelectApps         { "SELECT * FROM application" };
const std::string SelectTok          { "SELECT * FROM token WHERE access_token = (?) AND application_id = (?) AND status = 1" };
    
}
}
