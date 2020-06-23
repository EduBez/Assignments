#include "stdafx.h"

#include "Model.h"
#include "Typedefs.h"
#include "View.h"

using namespace std;
using namespace types;
using namespace Wt;

using namespace ::pplx;
using namespace concurrency::streams;
using namespace utility;
using namespace web::http::client;
using namespace web::http;

//
//  TModel
//
TModel::TModel(TViewModel* viewModel)
    // Member Initializer List
    : viewModel_ (viewModel)
    , opID_      (OpID::None)
{
    if (viewModel_ != nullptr)
    {
        // Initialize Callbacks
        op_ [OpID::Buy      ] = bind(&TViewModel::HttpResultHandler1 , viewModel_, _1);
        op_ [OpID::Codes    ] = bind(&TViewModel::HttpResultHandler2 , viewModel_, _1);
        op_ [OpID::Login    ] = bind(&TViewModel::HttpResultHandler3 , viewModel_, _1);
        op_ [OpID::Portfolio] = bind(&TViewModel::HttpResultHandler4 , viewModel_, _1);
        op_ [OpID::Quote    ] = bind(&TViewModel::HttpResultHandler5 , viewModel_, _1);
        op_ [OpID::Sell     ] = bind(&TViewModel::HttpResultHandler6 , viewModel_, _1);
        op_ [OpID::SignUp   ] = bind(&TViewModel::HttpResultHandler7 , viewModel_, _1);
        op_ [OpID::TransLog ] = bind(&TViewModel::HttpResultHandler8 , viewModel_, _1);
    }
}

// Http Actions
web::json::value TModel::HttpGet(OpID opID, const wstring& url)
{
    // Will be captured by the lambdas
    web::json::value result;

    http_client client(url);

    client.request(methods::GET)
    .then
    (
        [&](http_response response)
        {
            if (response.status_code() == status_codes::OK) {
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

    // Set dispatcher ID
    opID_ = opID;

    if (opID_ != OpID::None && !result.is_null())
    {
        // Invoke dispatcher
        auto func = op_[opID_];
        func(result);
    }

    return result;
}

web::json::value TModel::HttpPost(OpID opID, const wchar_t*  path,
                                             const wstring&  url,
                                             const web::json::value& json)
{
    // Will be captured by the lambdas
    web::json::value result;

    http_client client(url);

    client.request(methods::POST, path, json)
    .then
    (
        [&](http_response response)
        {
            if (response.status_code() == status_codes::OK) {
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

    // Set dispatcher ID
    opID_ = opID;

    if (opID_ != OpID::None && !result.is_null())
    {
        // Invoke dispatcher
        auto func = op_[opID_];
        func(result);
    }

    return result;
}
