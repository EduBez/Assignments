#pragma once
#include "Timer.h"

namespace evolve {
    namespace rest {

//
//  Application
//
class Application
{
    // Data Members
    std::wstring key_;
    std::wstring interval_;

    timer::Timer timer_;

    // Member Functions
    bool   Authenticate   ();

    void   Dispatch       (web::json::value& json);

    void   LoadConfigFile ();

    void   OnTimerTick    ();

public:
    // Def Ctor
    Application() {}

    void Run();
};

}};//EndOf namespace
// Namespace alias
namespace rest = evolve::rest;
