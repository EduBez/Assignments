#include "stdafx.h"
#include "Application.h"

using namespace rest;
using namespace std;

//
//  Main Entry Point
//
int main()
{
    try
    {
        // Run application
        Application app(L"http://localhost:9090/wIQserver_mt");
        app.Run();
    }
    catch (exception& e)
    {
        wcout << e.what() << endl;
        return 1;
    }

    return 0;
}
