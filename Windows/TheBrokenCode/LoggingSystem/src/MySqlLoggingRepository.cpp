#include "Constants.hpp"
#include "Model.hpp"
#include "LoggingRepository.hpp"

namespace brokencode {
namespace memory {
    
template <class T>
struct brokencode_default_delete final {
    brokencode_default_delete() noexcept {}
    void operator() (T *ptr) const noexcept {
        static_assert(sizeof(T) > 0, "brokencode_default_delete can not delete incomplete type");
        static_assert(!std::is_void<T>::value, "brokencode_default_delete can not delete incomplete type");
        using boost::typeindex::type_id_with_cvr;
        BOOST_LOG_TRIVIAL(info) << "brokencode_default_delete T: "
                                << type_id_with_cvr<T>().pretty_name()
                                << " param: "
                                << type_id_with_cvr<decltype(ptr)>().pretty_name();
        delete[] ptr;
    }
};
    
}
}

namespace brokencode {
namespace repository {

using model::User;
using model::Application;
using brokencode::memory::brokencode_default_delete;
    
class LoggingRepository::Impl {
public:
    using ConnectionPtr = std::unique_ptr<sql::Connection, brokencode_default_delete<sql::Connection>>;
    using StatementPtr = std::unique_ptr<sql::PreparedStatement, brokencode_default_delete<sql::PreparedStatement>>;
    using ResultSetPtr = std::unique_ptr<sql::ResultSet, brokencode_default_delete<sql::ResultSet>>;
    Impl() {
        Hostname = "tcp://127.0.0.1:3306";
        Username = "root";
        Password = "root";
        Driver = get_driver_instance();
    }
    auto CreateConnection() {
        ConnectionPtr connection(Driver->connect(Hostname, Username, Password));
        connection->setSchema(constants::DatabaseKey);
        return connection;
    }
    auto AddLogItem(const model::LogItem &logItem) {
        auto connection = CreateConnection();
        StatementPtr statement(connection->prepareStatement(constants::InsertLog));
        statement->setString(1, logItem.GetApplicationId());
        statement->setString(2, logItem.GetLogger());
        statement->setString(3, logItem.GetLevel());
        statement->setString(4, logItem.GetMessage());
        return statement->executeUpdate() > 0;
    }
    auto HasUser(const User &user) {
        auto connection = CreateConnection();
        StatementPtr statement(connection->prepareStatement(constants::SelectUser));
        statement->setString(1, user.GetId());
        statement->setString(2, user.GetSecret());
        ResultSetPtr resultSet(statement->executeQuery());
        return resultSet->first();
    }
    auto HasApplication(const Application &application) {
        auto result = false;
        try {
            auto connection = CreateConnection();
            StatementPtr statement(connection->prepareStatement(constants::SelectApp));
            statement->setString(1, application.GetId());
            statement->setString(2, application.GetSecret());
            ResultSetPtr resultSet(statement->executeQuery());
            result = resultSet->first();
        } catch (...) {
            BOOST_LOG_TRIVIAL(error) << "Unknown error";
        }
        return result;
    }
    auto AddApplication(const Application &application) {
        auto result = false;
        try {
            auto connection = CreateConnection();
            StatementPtr statement(connection->prepareStatement(constants::InsertApp));
            statement->setString(1, application.GetId());
            statement->setString(2, application.GetDisplayName());
            statement->setString(3, application.GetSecret());
            result = statement->executeUpdate() > 0;
        } catch (...) {
            BOOST_LOG_TRIVIAL(error) << "Unknown error";
        }
        return result;
    }
    auto CreateToken(const std::string &accessToken, const Application &application) {
        auto result = false;
        try {
            auto connection = CreateConnection();
            StatementPtr updateStat(connection->prepareStatement(constants::UpdateTok));
            updateStat->setString(1, application.GetId());
            updateStat->executeUpdate();
            StatementPtr insertStat(connection->prepareStatement(constants::InsertTok));
            insertStat->setString(1, accessToken);
            insertStat->setString(2, application.GetId());
            result = insertStat->executeUpdate() > 0;
        } catch (...) {
            BOOST_LOG_TRIVIAL(error) << "Unknown error";
        }
        return result;
    }
    auto IsAccessTokenValid(const std::string &accessToken, const std::string &applicationId) {
        auto result = false;
        try {
            auto connection = CreateConnection();
            StatementPtr statement(connection->prepareStatement(constants::SelectTok));
            statement->setString(1, accessToken);
            statement->setString(2, applicationId);
            ResultSetPtr resultSet(statement->executeQuery());
            result = resultSet->first();
        } catch (...) {
            BOOST_LOG_TRIVIAL(error) << "Unknown error";
        }
        return result;
    }
    std::vector<model::Application> GetApplications() {
        std::vector<model::Application> applications;
        try {
            auto connection = CreateConnection();
            StatementPtr statement(connection->prepareStatement(constants::SelectApps));
            ResultSetPtr resultSet(statement->executeQuery());
            while (resultSet->next()) {
                applications.push_back(model::Application(resultSet->getString("application_id"),
                                                          resultSet->getString("secret"),
                                                          resultSet->getString("display_name")));
            }
        } catch (...) {
            BOOST_LOG_TRIVIAL(error) << "Unknown error";
        }
        return applications;
    }
private:
    sql::SQLString Hostname;
    sql::SQLString Username;
    sql::SQLString Password;
    sql::Driver *Driver;
};
    
LoggingRepository::LoggingRepository() : PImpl { std::auto_ptr(new LoggingRepository::Impl) } {}
    
LoggingRepository::~LoggingRepository() {
    model::LogItem logItem("INFO",
                           "LOGGING_SYSTEM",
                           "SYSTEM TERMINATED",
                           "565e7b64-6277-4f08-aef7-bee17c77f97b");
    PImpl->AddLogItem(logItem);
}
    
bool LoggingRepository::AddLogItem(const model::LogItem &logItem) noexcept {
    return PImpl->AddLogItem(logItem);
}

bool LoggingRepository::HasUser(const User &user) noexcept {
    return PImpl->HasUser(user);
}
    
bool LoggingRepository::HasApplication(const Application &application) noexcept {
    return PImpl->HasApplication(application);
}

bool LoggingRepository::AddApplication(const Application &application) noexcept {
    return PImpl->AddApplication(application);
}

bool LoggingRepository::CreateToken(const std::string &accessToken, const Application &application) noexcept {
    return PImpl->CreateToken(accessToken, application);
}

bool LoggingRepository::IsAccessTokenValid(const std::string &accessToken, const std::string &applicationId) noexcept {
    return PImpl->IsAccessTokenValid(accessToken, applicationId);
}
    
std::vector<model::Application> LoggingRepository::GetApplications() noexcept {
    return PImpl->GetApplications();
}

}
}
