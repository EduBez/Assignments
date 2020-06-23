#pragma once
#include "stdafx.h"

#include "DAL/DataAccessLayer.h"

namespace Evolve {
    namespace Rest {

//
//  RESTfull
//
class RESTfull
{
    // Data Member 
    web::http::experimental::listener::http_listener listener_;

    // Event handler
    void handle_get(web::http::http_request request);

    // Message Pool
    void DoListen();

public:
    // Ctor
    RESTfull(const web::http::uri& url);

    void Listen();
};

}};//EndOf namespace
// Namespace alias
namespace rest = Evolve::Rest;
