#pragma once
#include "stdafx.h"

#include "Windows.h"
#include <thread>

namespace evolve {
    namespace timer {

// Event Handler Type
using TimerHandler = std::function<void()>;

//
//  Timer
//
class Timer
{
    // Timer Handle
    UINT_PTR handle_;

    // Timer Interval (in seconds)
    int interval_;

    // Timer Callback
    static VOID CALLBACK OnTimer(HWND hWnd, UINT msg, UINT event, DWORD time);

public:
    // Def Ctor
    Timer() {}

    // Ctor
    Timer(int interval);

    // Dtor
    ~Timer();

    void Start ();
    void Stop  ();

    // Event Handler
    static TimerHandler Tick;
};

}};//EndOf namespace
// Namespace alias
namespace timer = evolve::timer;
