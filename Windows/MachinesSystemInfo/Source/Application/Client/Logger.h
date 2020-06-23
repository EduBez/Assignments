#pragma once
#include "stdafx.h"

namespace evolve {
    namespace logger {

//
//  Logger
//
class Logger : private boost::noncopyable
{
    // Data members
    static std::wofstream log_;

public:
    // Dtor
    ~Logger();

    // Member Functions
    static void Open  (const std::wstring& file);

    // Member Functions Templates
    template <typename T>
    static void Write(T arg)
    {
        std::wcout << arg << std::endl;
        log_       << arg << std::endl;
        log_.flush();
    }

    template <typename T1, typename T2>
    static void Write(T1 arg1, T2 arg2)
    {
        std::wcout << arg1 << arg2 << std::endl;
        log_       << arg1 << arg2 << std::endl;
        log_.flush();
    }
};

}};//EndOf namespace
// Namespace alias
namespace lgr = evolve::logger;
