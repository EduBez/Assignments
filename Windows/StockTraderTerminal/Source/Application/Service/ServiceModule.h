#pragma once
#include "stdafx.h"

namespace evolve {
    namespace rest {

//
//  ServiceModule
//
class ServiceModule
{
    // Data Members
    web::http::experimental::listener::http_listener listener_;

    // Member Functions
    void Listen       ();
    
    bool Authenticate (const std::wstring& user,
                       const std::wstring& pwd);
    
    bool AddNewUser   (const std::wstring& user,
                       const std::wstring& pwd);

    bool BuyStock     (const std::wstring& user,
                       const std::wstring& pwd,
                       const std::wstring& stock,
                       const std::wstring& quantity,
                       const std::wstring& price);

    bool SellStock    (const std::wstring& user,
                       const std::wstring& pwd,
                       const std::wstring& stock,
                       const std::wstring& quantity,
                       const std::wstring& price);

    web::json::value GetStockCodes    ();

    web::json::value GetStockQuote    (const std::wstring& user,
                                       const std::wstring& pwd ,
                                       const std::wstring& code);

    web::json::value ViewPortfolio    (const std::wstring& user,
                                       const std::wstring& pwd);

    web::json::value ViewTransactions (const std::wstring& user,
                                       const std::wstring& pwd);

public:
    // Ctor
    ServiceModule(const web::http::uri& url);

    // Http Handlers
    void HandleGET  (web::http::http_request request);
    void HandlePOST (web::http::http_request request);

    // Message Pool
    void Run();
};

}};//EndOf namespace
// Namespace alias
namespace rest = evolve::rest;
