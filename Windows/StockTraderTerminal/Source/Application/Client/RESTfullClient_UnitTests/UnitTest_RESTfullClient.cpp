#include "stdafx.h"

#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//  Main Project Headers
#include "../Model.h"

using namespace std;
using namespace types;

namespace RESTfullClient_UnitTests
{		
    // Attention: Must have internet connection to run
    TEST_CLASS(UnitTest1)
    {
        public:
            TEST_METHOD(TestMethod1)
            {
                unique_ptr<TModel> model = make_unique<TModel>(nullptr);
                
                web::json::value json = model->HttpGet
                    (OpID::None, L"http://echo.jsontest.com/title/ipsum/content/blah");
                
                wstring w = json[L"content"].as_string();
                wstring r = L"blah";
                
                Assert::AreEqual(w, r);
            }
            
            // Attention:  Must have internet connection to run
            TEST_METHOD(TestMethod2)
            {
                unique_ptr<TModel> model = make_unique<TModel>(nullptr);
                
                web::json::value json = model->HttpGet
                    (OpID::None, L"http://echo.jsontest.com/title/ipsum/content/blah");
                
                wstring w = json[L"title"].as_string();
                wstring r = L"ipsum";
                
                Assert::AreEqual(w, r);
            }
    };
}