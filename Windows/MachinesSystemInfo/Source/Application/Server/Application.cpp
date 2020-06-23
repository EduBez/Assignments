#include "stdafx.h"
#include "Windows.h"

#include "Application.h"
#include "Typedefs.h"
#include "SMTP.h"

using namespace dal;
using namespace meta;
using namespace parser;
using namespace rest;
using namespace smtp;
using namespace std;
using namespace types;

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

//
//  Application
//

// Ctor
Application::Application(const http::uri& url)
    // Member Initializer List
    : listener_(http_listener(url))
{
    auto func1 = bind(&Application::HandleGET , this, placeholders::_1);
    auto func2 = bind(&Application::HandlePOST, this, placeholders::_1);

    listener_.support(methods::GET , func1);
    listener_.support(methods::POST, func2);
}

void Application::Listen()
{
    try
    {
        listener_.open()
        .then
        (
            []()
            {
                wcout << L"[wIQserver_mt] Listening for clients..."
                      << endl;
            }
        )
        .wait();
    }
    catch (const exception& e) {
        wcout << e.what() << endl;
    }
}

void Application::HandleGET(http_request request)
{
    try
    {
        web::json::value result;

        auto uri = request.request_uri().to_string();

        vector<wstring> args;
        boost::split(args, uri, boost::is_any_of("/"));

        if (args.size() == 4)
        {
            if (!args[2].empty() && !args[3].empty())
            {
                if (args[2] == L"Authenticate")
                {
                    // Authenticate client
                    result = Authenticate(args[3]);
                }
                // Return response
                request.reply(status_codes::OK, result);
            }
        }
        else {
            request.reply(status_codes::NotFound);    
        }
    }
    catch (const exception& e) {
        wcout << e.what() << endl;
    }
}

void Application::HandlePOST(http_request request)
{
    try
    {
        web::json::value result;

        auto uri = request.request_uri().to_string();

        vector<wstring> args;
        boost::split(args, uri, boost::is_any_of("/"));

        if (args.size() == 3)
        {
            if (args[2] == L"Instrumentation")
            {
                auto json = request.extract_json(true);
                auto info = json.get().as_array();

                // WMIThreshold client
                Instrumentate(info);

                result = true;
            }
            // Return response
            request.reply(status_codes::OK, result);
        }
        else {
            request.reply(status_codes::NotFound);
        }
    }
    catch (const exception& e) {
        wcout << e.what() << endl;
    }
}

bool Application::Authenticate(const std::wstring& key)
{
    wstring msg = L"[wIQserver_mt] Authenticating client with ID [%1%]";
    msg = boost::str(boost::wformat(msg) % key);
    wcout << msg << endl;

    string id = string(key.begin(), key.end());

    // Authenticate client machine
    DataAccessLayer dac;
    return dac.Authenticate(id);
}

string Application::ComposeAlertMSg(const ClientInfo& info)
{
    string msg = "Client Machine [%1%]\nMemory: %2%\nCPU: %3%\nProcesses: %4%\n";

    msg = boost::str(boost::format(msg) % info.key
                                        % info.memory
                                        % info.cpu
                                        % info.processes);
    return msg;
}

void Application::Instrumentate(web::json::array& info)
{
    wstring key = info[0].as_string();
    wstring msg = L"[wIQserver_mt] Receiving instrumentation from client with ID [%1%]";

    msg = boost::str(boost::wformat(msg) % key);
    wcout << msg << endl;

    string cik(info[0].as_string().begin(), info[0].as_string().end());
    string cim(info[1].as_string().begin(), info[1].as_string().end());
    string ciu(info[2].as_string().begin(), info[2].as_string().end());
    string cip(info[3].as_string().begin(), info[3].as_string().end());

    ClientInfo client {cik, ""/*dummy*/, cim, ciu, cip};

    // Retrieve threshold levels
    DataAccessLayer dac;
    ClientInfo server = dac.WMIThreshold(cik);

    // Compare thresholds
    if (client.memory    != server.memory ||
        client.cpu       != server.cpu    ||
        client.processes != server.processes)
    {
        // Update client email
        client.mail = server.mail;

        // Send threshold alert
        SendAlert(dac, client);
    }
}

bool Application::LoadConfigFile()
{
    bool result = false;

    wstring msg = L"[wIQserver_mt] Loading clients configuration into database";
    wcout << msg << endl;

    // Parse XML config file
    Machines mi = ConfigParser::Parse();

    if (result = (mi.size() != 0))
    {
        // Load client machines from config file into the database
        DataAccessLayer dac;
        result = dac.Populate(mi);
    }

    return result;
}

void Application::Run()
{
    if (!LoadConfigFile())
    {
        wcout << L"[wIQserver_mt] Error loading clients configuration into database"
              << endl
              << L"[wIQserver_mt] Server is closing"
              << endl;

        // Wait 5 secs before shutting down
        Sleep(5000);
        return;
    }

    HANDLE h = ::OpenThread(THREAD_ALL_ACCESS, false, GetCurrentThreadId());

    // Start listening for clients
    Listen();

    // Suspend the main thread
    SuspendThread(h);
}

void Application::SendAlert(DataAccessLayer& dac, const ClientInfo& info)
{
    try
    {
        // Write alert to 'MachineUtilization' table
        dac.WMIAlert(info);

        // Compose email subject
        string msg = ComposeAlertMSg(info);

        // Send email alert notification
        SMTP mail("smtp.dummy.com", 25, "EduBez@dummy.com", "MyPassword");

        mail.Send("EduBez@dummy.com", info.mail, "wIQserver_mt WMI Alert", msg);
    }
    catch (exception& e) {
        wcout << e.what() << endl;
    }
}
