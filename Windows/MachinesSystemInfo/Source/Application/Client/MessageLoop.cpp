#include "stdafx.h"
#include "MessageLoop.h"

using namespace loop;

// Statics definition
HWND MessageLoop::Handle = NULL;

//
//  MessageLoop
//
long __stdcall MessageLoop::Procedure(HWND     hWnd,
                                      unsigned msg,
                                      WPARAM   wp,
                                      LPARAM   lp)
{
    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0L;

        default:
            return DefWindowProc(hWnd, msg, wp, lp);
    }
}

void MessageLoop::Start()
{
    const wchar_t* c = L"wIQclass";
    const wchar_t* t = L"wIQtitle";

    HMODULE  module  =  GetModuleHandle(0);
    HICON    icon    =  LoadIcon(0, IDI_APPLICATION);
    HCURSOR  cursor  =  LoadCursor(0, IDC_ARROW);
    HBRUSH   brush   =  HBRUSH(COLOR_WINDOW + 1);

    WNDCLASSEX window =
        {sizeof(WNDCLASSEX), CS_DBLCLKS, Procedure, 0, 0, module, icon, cursor, brush, 0, c, icon};

    if (RegisterClassEx(&window))
    {
        Handle = CreateWindowEx(0
                              , c
                              , t
                              , WS_OVERLAPPEDWINDOW
                              , CW_USEDEFAULT
                              , CW_USEDEFAULT
                              , CW_USEDEFAULT
                              , CW_USEDEFAULT
                              , 0
                              , 0
                              , module
                              , 0);
        if (Handle)
        {
            // The window must be hidden
            ShowWindow(Handle, SW_HIDE);

            MSG msg;
            while (GetMessage(&msg, 0, 0, 0)) DispatchMessage(&msg);
        }
    }
}
