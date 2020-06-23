#include "stdafx.h"
#include "Windows.h"

#include "ServiceModule.h"
#include "JSONDataModule.h"

using namespace dal;
using namespace rest;
using namespace std;

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace web::json;

//
//  ServiceModule
//

// Ctor
ServiceModule::ServiceModule(const http::uri& url)
    // Member Initializer List
    : listener_(http_listener(url))
{
    auto func1 = bind(&ServiceModule::HandleGET , this, placeholders::_1);
    auto func2 = bind(&ServiceModule::HandlePOST, this, placeholders::_1);

    listener_.support(methods::GET , func1);
    listener_.support(methods::POST, func2);
}

void ServiceModule::Run()
{
    HANDLE h = ::OpenThread(THREAD_ALL_ACCESS, false, GetCurrentThreadId());

    // Start listening for clients
    Listen();

    // Suspend the main thread
    SuspendThread(h);
}

void ServiceModule::Listen()
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

void ServiceModule::HandleGET(http_request request)
{
    try
    {
        web::json::value result;
        auto uri = request.request_uri().to_string();

        vector<wstring> args;
        boost::split(args, uri, boost::is_any_of("/"));

        if (args.size() >= 3)
        {
            // REST End Points
            if (args[2] == L"Login")
            {
                result = Authenticate(args[3], args[4]);
            }
            else if (args[2] == L"StockCodes")
            {
                result = GetStockCodes();
            }
            else if (args[2] == L"StockQuote")
            {
                result = GetStockQuote(args[3], args[4], args[5]);
            }
            else if (args[2] == L"Transactions")
            {
                result = ViewTransactions(args[3], args[4]);
            }
            else if (args[2] == L"Portfolio")
            {
                result = ViewPortfolio(args[3], args[4]);
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

void ServiceModule::HandlePOST(http_request request)
{
    try
    {
        web::json::value result;

        auto uri = request.request_uri().to_string();

        vector<wstring> args;
        boost::split(args, uri, boost::is_any_of("/"));

        if (args.size() >= 3)
        {
            // End Points
            if (args[2] == L"SignUp")
            {
                auto json = request.extract_json(true);
                auto info = json.get().as_array();

                result = AddNewUser(info[0].as_string(),
                                    info[1].as_string());
            }
            else if (args[2] == L"StockBuy")
            {
                auto json = request.extract_json(true);
                auto info = json.get().as_array();

                result = BuyStock(info[0].as_string(),
                                  info[1].as_string(),
                                  info[2].as_string(),
                                  info[3].as_string(),
                                  info[4].as_string());
            }
            else if (args[2] == L"StockSell")
            {
                auto json = request.extract_json(true);
                auto info = json.get().as_array();

                result = SellStock(info[0].as_string(),
                                   info[1].as_string(),
                                   info[2].as_string(),
                                   info[3].as_string(),
                                   info[4].as_string());
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

bool ServiceModule::Authenticate(const wstring& user, const wstring& pwd)
{
    string arg1(user.begin(), user.end());
    string arg2(pwd. begin(), pwd. end());

    JSONDataModule dac;
    return dac.Authenticate(arg1, arg2);
}

bool ServiceModule::AddNewUser(const wstring& user, const wstring& pwd)
{
    string arg1(user.begin(), user.end());
    string arg2(pwd. begin(), pwd. end());

    JSONDataModule dac;
    return dac.AddNewUser(arg1, arg2);
}

bool ServiceModule::BuyStock(const std::wstring& user,
                             const std::wstring& pwd,
                             const std::wstring& stock,
                             const std::wstring& quantity,
                             const std::wstring& price)
{
    string arg1(user     .begin(),  user     .end());
    string arg2(pwd      .begin(),  pwd      .end());
    string arg3(stock    .begin(),  stock    .end());
    string arg4(quantity .begin(),  quantity .end());
    string arg5(price    .begin(),  price    .end());

    JSONDataModule dac;
    return dac.BuyStock(arg1, arg2, arg3, arg4, arg5);
}

bool ServiceModule::SellStock(const std::wstring& user,
                              const std::wstring& pwd,
                              const std::wstring& stock,
                              const std::wstring& quantity,
                              const std::wstring& price)
{
    string arg1(user     .begin(),  user     .end());
    string arg2(pwd      .begin(),  pwd      .end());
    string arg3(stock    .begin(),  stock    .end());
    string arg4(quantity .begin(),  quantity .end());
    string arg5(price    .begin(),  price    .end());

    JSONDataModule dac;
    return dac.SellStock(arg1, arg2, arg3, arg4, arg5);
}

web::json::value ServiceModule::GetStockCodes()
{
    JSONDataModule dac;
    return dac.GetStockCodes();
}

web::json::value ServiceModule::GetStockQuote(const std::wstring& user,
                                              const std::wstring& pwd ,
                                              const std::wstring& code)
{
    string arg1(user.begin(), user.end());
    string arg2(pwd. begin(), pwd. end());
    string arg3(code.begin(), code.end());

    JSONDataModule dac;
    return dac.GetStockQuote(arg1, arg2, arg3);
}

web::json::value ServiceModule::ViewPortfolio(const std::wstring& user,
                                              const std::wstring& pwd)
{
    string arg1(user.begin(), user.end());
    string arg2(pwd. begin(), pwd. end());

    JSONDataModule dac;
    return dac.ViewPortfolio(arg1, arg2);
}

web::json::value ServiceModule::ViewTransactions (const std::wstring& user,
                                                  const std::wstring& pwd)
{
    string arg1(user.begin(), user.end());
    string arg2(pwd. begin(), pwd. end());

    JSONDataModule dac;
    return dac.ViewTransactions(arg1, arg2);
}
