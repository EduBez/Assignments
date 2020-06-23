#include "stdafx.h"
#include "View.h"

//
// Factory Function
//
Wt::WApplication* CreateWebApp(const Wt::WEnvironment& env)
{
    return new TView(env);
}

//
//  Main Entry Point
//
int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, &CreateWebApp);
}
