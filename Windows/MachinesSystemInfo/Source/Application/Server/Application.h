#pragma once
#include "stdafx.h"

#include "DataAccessLayer.h"
#include "Metadata.h"

namespace evolve {
    namespace rest {

//
//  Application
//
class Application
{
    // Data Members
    web::http::experimental::listener::http_listener listener_;

    // Event handlers
    void HandleGET  (web::http::http_request request);
    void HandlePOST (web::http::http_request request);

    // Member Functions
    bool        Authenticate      (const std::wstring& key);

    std::string ComposeAlertMSg   (const meta::ClientInfo& info);

    void        Instrumentate     (web::json::array& info);

    void        SendAlert         (dal::DataAccessLayer& dac,
                                   const meta::ClientInfo& info);

    bool        LoadConfigFile    ();

    void        Listen            ();

public:
    // Ctor
    Application(const web::http::uri& url);

    // Message Pool
    void Run();
};

}};//EndOf namespace
// Namespace alias
namespace rest = evolve::rest;
