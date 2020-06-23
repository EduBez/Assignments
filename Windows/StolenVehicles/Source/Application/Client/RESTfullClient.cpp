#include "stdafx.h"
#include "WtDesignUi.h"

//
// Factory Function
//
Wt::WApplication* CreateWebApp(const Wt::WEnvironment& env)
{
    return new WtDesignUi(env);
}

//
//  Main Entry Point
//
int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, &CreateWebApp);
}
