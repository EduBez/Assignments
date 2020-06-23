#include "stdafx.h"
#include "Timer.h"

using namespace timer;

// Statics definition
TimerHandler Timer::Tick = nullptr;

//
//  Timer
//

// Ctor
Timer::Timer(int interval)
    // Member Initialization List
    : handle_(0)
{
    // Interval in SECS
    interval_ = (interval * 100);
}

// Dtor
Timer::~Timer()
{
    if (handle_) KillTimer(NULL, handle_);
}

void Timer::Start()
{
    handle_ = SetTimer(NULL, 0, interval_, &Timer::OnTimer);
}

void Timer::Stop()
{
    KillTimer(NULL, handle_);
}

VOID CALLBACK Timer::OnTimer(HWND hWnd, UINT msg, UINT event, DWORD time)
{
    if (Tick) Tick();
}
