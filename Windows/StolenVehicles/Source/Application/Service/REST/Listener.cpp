#include "stdafx.h"

#include "Listener.h"
using namespace rest;

using namespace dal;
using namespace dml;
using namespace mtd;

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

//
//  RESTfull
//

// Ctor
RESTfull::RESTfull(const http::uri& url)
    // Member Initializer List
    : listener_(http_listener(url))
{
    auto func = bind(&RESTfull::handle_get, this, placeholders::_1);

    listener_.support(methods::GET, func);
}

void RESTfull::Listen()
{
    HANDLE h = OpenThread(THREAD_ALL_ACCESS, false, GetCurrentThreadId());

    // Start listening for requests
    DoListen();

    // Suspend the main thread
    SuspendThread(h);
}

void RESTfull::DoListen()
{
    try
    {
        listener_.open()
        .then
        (
            []()
            {
                wcout << L"RESTfullService is listening for requests..."
                      << endl;
            }
        )
        .wait();
    }
    catch (const exception& e) {
        wcout << e.what() << endl;
    }
}

void RESTfull::handle_get(http_request request)
{
    try
    {
        auto uri = request.request_uri().to_string();

        vector<wstring> args;
        boost::split(args, uri, boost::is_any_of("/"));

        if (args.size() == 4)
        {
            if (!args[2].empty() && !args[3].empty())
            {
                Column col = DalMetaData::ColumnID(args[2]);

                // Perform database search
                dal::DataAccessLayer dac;
                json_array_t recs = dac.Query(col, args[3]);

                // Return response
                request.reply(status_codes::OK, web::json::value::object(recs));
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
