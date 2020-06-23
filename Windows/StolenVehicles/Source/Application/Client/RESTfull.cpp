#include "stdafx.h"

#include "RESTfull.h"
using namespace rest;

using namespace std;

using namespace ::pplx;
using namespace concurrency::streams;
using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace Wt;

//
//  Invoke
//
void RESTfull::Invoke(CallBack func, const WString& uri, const WString& value)
{
    // Will be captured by the lambdas
    web::json::value result;

    wstring url = L"http://localhost:9090/RESTfull/%1%/%2%";
    url = boost::str(boost::wformat(url) % uri % value);
    
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
                result = json_value.get();
            }
            catch (const http_exception& e) {
                wcout << e.what() << endl;
            }
        }
    )
    .wait();

    // At this point the parallel task ended
    // Handle the received data
    func(result);
}
