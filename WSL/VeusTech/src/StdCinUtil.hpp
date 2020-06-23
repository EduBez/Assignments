#ifndef StdCinUtilHPP
    #define StdCinUtilHPP

#include "PreCompH.hpp"

#ifdef __GNUC__
    #include <termios.h>
    #include <unistd.h>

#elif _MSC_VER
    #define VC_EXTRALEAN
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif

namespace veus {

// Type alias
using VecStr = std::vector<std::string>;

//
//  Redirects the standard input 'std::cin' to a given file
//
class CinRedir
{
    std::string file_;
    std::streambuf* buf_;
    std::ifstream in_;
    
public:    
    // Ctor
    explicit CinRedir(std::string file);
    // Dtor
    ~CinRedir();
};

//
//  Turn off echo for any standard input function
//
class CinEchOff
{
#ifdef __GNUC__
    termios def_;
    
#elif _MSC_VER
    HANDLE handle_;
    DWORD mode_;
#endif

public:
    // Ctor
    CinEchOff();
    // Dtor
    ~CinEchOff();
};

}//EndOf namespace

#endif
