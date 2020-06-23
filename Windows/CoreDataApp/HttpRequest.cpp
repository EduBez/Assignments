#include "StdAfx.h"
#include "HttpRequest.h"

using namespace std;

using namespace ::pplx;
using namespace web::http::client;
using namespace web::http;

///////////////////////////////////////////////////////////////////////////////
//  Rest
//
wstring Rest::HttpGet(const wstring& url)
{
    // Will be captured by the lambda
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
    return result.serialize();
}
