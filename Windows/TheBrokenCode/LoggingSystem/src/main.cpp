#include "LoggingSystem.hpp"
#include "LoggingServer.hpp"

int main(int argc, const char *argv[]) {
    BOOST_LOG_TRIVIAL(info) << boost::format("Logging System version %d.%d.%d") %
                               brokencode::LoggingSystemVersionMajor             %
                               brokencode::LoggingSystemVersionMinor             %
                               brokencode::LoggingSystemVersionPatch;
    if (argc < 2) {
        BOOST_LOG_TRIVIAL(info) << "Please provide the port number";
        return -1;
    }
    utility::string_t port = U(argv[1]);
    utility::string_t url = U("http://localhost:");
    url.append(port);
    brokencode::server::LoggingServer server(url);
    try {
        server.Start();
        std::string line;
        std::getline(std::cin, line);
        server.Stop();
    } catch (const std::exception &e) {
        BOOST_LOG_TRIVIAL(error) << "Error::" << e.what();
    }
    return 0;
}
