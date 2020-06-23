#pragma once
#include "stdafx.h"

#include <windows.h>

namespace evolve {
    namespace loop {

//
//  MessageLoop
//
class MessageLoop : private boost::noncopyable
{
    static long __stdcall Procedure(HWND     hWnd,
                                    unsigned msg,
                                    WPARAM   wp,
                                    LPARAM   lp);
public:
    static void Start();

    // Data Members
    static HWND Handle;
};

}};//EndOf namespace
// Namespace alias
namespace loop = evolve::loop;
