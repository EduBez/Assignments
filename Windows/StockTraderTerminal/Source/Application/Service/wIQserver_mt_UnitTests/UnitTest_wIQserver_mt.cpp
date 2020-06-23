#include "stdafx.h"

#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//  Main Project Headers
#include "../JSONDataModule.h"

using namespace dal;
using namespace std;

namespace wIQserver_mt_UnitTests
{		
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestMethod1)
        {
            JSONDataModule dac;
            bool r = dac.Authenticate("user1", "pwd1");
            
            Assert::AreEqual(r, false);
        }
        
        TEST_METHOD(TestMethod2)
        {
            sql::SQLString sql = "dummy";
            wstring ws = L"dummy";
            
            JSONDataModule dac;
            wstring r = dac.S(sql);
            
            Assert::AreEqual(ws, r);
        }
        
        TEST_METHOD(TestMethod3)
        {
            JSONDataModule dac;
            bool r = dac.AddNewUser("dummy1", "dummy2");
            
            Assert::AreEqual(r, false);
        }
        
        TEST_METHOD(TestMethod4)
        {
            const std::string& user     = "dummy1";
            const std::string& pwd      = "dummy2";
            const std::string& stock    = "dummy3";
            const std::string& quantity = "dummy4";
            const std::string& price    = "dummy5";
            
            JSONDataModule dac;
            bool r = dac.BuyStock(user, pwd, stock, quantity, price);
            
            Assert::AreEqual(r, false);
        }
        
        TEST_METHOD(TestMethod5)
        {
            const std::string& user     = "dummy1";
            const std::string& pwd      = "dummy2";
            const std::string& stock    = "dummy3";
            const std::string& quantity = "dummy4";
            const std::string& price    = "dummy5";
            
            JSONDataModule dac;
            bool r = dac.SellStock(user, pwd, stock, quantity, price);
            
            Assert::AreEqual(r, false);
        }
    };
}
