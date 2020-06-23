#include "stdafx.h"
#include "ServiceModule.h"

using namespace rest;
using namespace std;

//
//  Main Entry Point
//
int main()
{
    try
    {
        // Run service
        ServiceModule srvc(L"http://localhost:9090/wIQserver_mt");
        srvc.Run();
    }
    catch (exception& e)
    {
        wcout << e.what() << endl;
        return 1;
    }

    return 0;
}
