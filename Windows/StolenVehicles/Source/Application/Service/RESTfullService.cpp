#include "stdafx.h"

#include "REST/Listener.h"
using namespace rest;

//
//  Main Entry Point
//
int main()
{
    RESTfull r(L"http://localhost:9090/RESTfull");
    r.Listen();
 
    return 0;
}
