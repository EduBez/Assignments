#pragma once
#include "stdafx.h"

#include <windows.h>
#include <TlHelp32.h>
#include <pdh.h>

namespace evolve {
    namespace wmi {

//
//  WMI
//
class WMI : private boost::noncopyable
{
    static const int MB = 1048576;

public:
    // Member Functions
    static std::wstring Memory    ();

    static std::wstring CPU       ();

    static std::wstring Processes ();
};

}};//EndOf namespace
// Namespace alias
namespace wmi = evolve::wmi;
