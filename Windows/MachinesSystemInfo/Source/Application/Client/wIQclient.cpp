#include "stdafx.h"
#include "Application.h"
#include "Logger.h"

using namespace lgr;
using namespace rest;
using namespace std;

//
//  Main Entry Point
//
int main()
{
    try
    {
        // Open global log
        Logger::Open(L"wIQclient.log");

        // Create and run the Application
        Application app;
        app.Run();
    }
    catch (exception& e)
    {
        wcout << e.what() << endl;
        return 1;
    }

    return 0;
}
