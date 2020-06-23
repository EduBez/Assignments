#include "stdafx.h"

#include "Application.h"
#include "Logger.h"
#include "Instrumentation.h"
#include "MessageLoop.h"

using namespace lgr;
using namespace loop;
using namespace rest;
using namespace timer;
using namespace wmi;

using namespace ::pplx;
using namespace concurrency::streams;
using namespace std;
using namespace utility;
using namespace web::http::client;
using namespace web::http;

using boost::property_tree::ptree;

//
//  Application
//
bool Application::Authenticate()
{
    wstring msg = boost::str(boost::wformat
        (L"[wIQclient] Authenticating client [key: %1%]") % key_);

    Logger::Write(msg);

    bool result = false;

    if (!key_.empty())
    {
        try
        {
            // Will be captured by the lambdas
            web::json::value json;

            wstring url = L"http://localhost:9090/wIQserver_mt/Authenticate/%1%";

            url = boost::str(boost::wformat(url) % key_);

            http_client client(url);

            client.request(methods::GET)
            .then
            (
                [&](http_response response)
                {
                    if (response.status_code() == status_codes::OK)
                    {
                        return response.extract_json();
                    }

                    // Handle return codes != status_codes::OK
                    return pplx::task_from_result(web::json::value());
                }
            )
            .then
            (
                [&](pplx::task<web::json::value> json_value)
                {
                    try {
                        json = json_value.get();
                    }
                    catch (const http_exception& e)
                    {
                        wstring msg = boost::str(boost::wformat
                            (L"[wIQclient] Authentication error: %1%") % e.what());

                        Logger::Write(msg);
                    }
                }
            )
            .wait();

            if (!json.is_null()) {
                result = (json.as_integer() != 0);
            }
        }
        catch (const exception& e)
        {
            wstring msg = boost::str(boost::wformat
                (L"[wIQclient] Error: Server authentication failure [key: %1%]") % key_);

            Logger::Write(e.what(), msg);
        }
    }

    return result;
}

void Application::LoadConfigFile()
{
    wstring msg = L"[wIQclient] Loading client data from config file";
    Logger::Write(msg);

    // Stream for XML file reading
    ifstream fs;

    try
    {
        // Load client KEY from 'client.config.xml'
        fs.open("client.config.xml");

        // Populate tree structure
        ptree pt;
        read_xml(fs, pt);

        for (auto const& ref : pt.get_child("machine"))
        {
            if (ref.first == "client")
            {
                // Extracts the KEY
                string s = ref.second.get<string>("key");
                key_ = wstring(s.begin(), s.end());

                // Extracts the INTERVAL
                s = ref.second.get<string>("interval");
                interval_ = wstring(s.begin(), s.end());
            }
        }
    }
    catch (exception& e)
    {
        wstring msg = L"[wIQclient] Error: Retrieving data from config file";
        Logger::Write(e.what(), msg);
    }
}

void Application::Run()
{
    // Retrieve client key & interval from XML config file
    LoadConfigFile();

    if (Authenticate())
    {
        try
        {
            int interval = boost::lexical_cast<int>(interval_);

            // Create Timer
            timer_ = Timer(interval);

            // Assign the Timer event handler
            timer_.Tick = std::bind(&Application::OnTimerTick, this);

            // Activate the Timer
            timer_.Start();
        }
        catch (exception& e)
        {
            wstring msg = boost::str(boost::wformat
                (L"[wIQclient] Error: Unable to create timer [key: %1%]") % key_);

            Logger::Write(e.what(), msg);
        }
    }
    else
    {
        wstring msg = boost::str(boost::wformat
            (L"[wIQclient] Error: Unable to authenticate client [key: %1%]") % key_);

        Logger::Write(msg);

        msg = L"[wIQclient] Error: Client is closing";
        Logger::Write(msg);

        // Wait 5 secs before shutting down
        Sleep(5000);
        return;
    }

    // Create a hidden window with a message loop
    // This will keep the client app running
    MessageLoop::Start();
}

void Application::OnTimerTick()
{
    // Stop timer to avoid recursion
    timer_.Stop();

    wstring msg = boost::str(boost::wformat
        (L"[wIQclient] Retrieving instrumentation info for client [key: %1%]") % key_);

    Logger::Write(msg);

    auto json = web::json::value::array();

    json[0] = web::json::value(key_);
    // WMI info
    json[1] = web::json::value(WMI::Memory());
    json[2] = web::json::value(WMI::CPU());
    json[3] = web::json::value(WMI::Processes());

    // Dispatch system info to the server
    Dispatch(json);
}

void Application::Dispatch(web::json::value& json)
{
    wstring msg = boost::str(boost::wformat
        (L"[wIQclient] Dispatching client [key: %1%] instrumentation to server") % key_);

    Logger::Write(msg);

    // Will be captured by the lambdas
    web::json::value result;

    wstring url = L"http://localhost:9090/wIQserver_mt/";

    try
    {
        http_client client(url);

        client.request(methods::POST, L"/Instrumentation", json)
        .then
        (
            [&](http_response response)
            {
                if (response.status_code() == status_codes::OK)
                {
                    return response.extract_json();
                }

                // Handle return codes != status_codes::OK
                return pplx::task_from_result(web::json::value());
            }
        )
        .then
        (
            [&](pplx::task<web::json::value> json_value)
            {
                try {
                    result = json_value.get();
                }
                catch (const http_exception& e) {
                    wcout << e.what() << endl;
                }
            }
        )
        .wait();
    }
    catch (const exception& e)
    {
        wstring msg = boost::str(boost::wformat
            (L"[wIQclient] Error: Dispatching client [key: %1%] instrumentation to server") % key_);

        Logger::Write(e.what(), msg);
    }

    // At this point the parallel task ended
    // Now we can re-activate the timer
    timer_.Start();
}
