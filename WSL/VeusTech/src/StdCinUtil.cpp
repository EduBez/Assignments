#include "StdCinUtil.hpp"

using namespace std;
using namespace veus;

//
//  Redirects the standard input 'std::cin' to a given file
//

// Ctor
CinRedir::CinRedir(string file)
    // Member initialization list
    : file_(move(file))
{
    // Save 'cin' standard stream buffer
    buf_ = cin.rdbuf();

    // Redirect 'std::cin'
    cin.rdbuf(in_.rdbuf());

    // Open file for reading
    in_.open(file_);
}

// Dtor
CinRedir::~CinRedir()
{
    // Close the file
    in_.close();
    // Restore 'cin' to standard stream buffer
    cin.rdbuf(buf_);
}

//
//  Turn off echo for any standard input function
//

// Ctor
CinEchOff::CinEchOff()
    #ifdef __GNUC__
    : def_{0,0,0,0,0,{0},0,0}
    #endif
{
    // Disable echo 
#ifdef __GNUC__
    tcgetattr(STDIN_FILENO, &def_);
    termios term{def_};

    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

#elif _MSC_VER
    handle_ = GetStdHandle(STD_INPUT_HANDLE);
    mode_ = 0;
    GetConsoleMode(handle_, &mode_);

    DWORD mode{mode_};
    mode &= ~ENABLE_ECHO_INPUT;
    SetConsoleMode(handle_, mode);
#endif
}

// Dtor
CinEchOff::~CinEchOff()
{
    // Restore echo
#ifdef __GNUC__
    tcsetattr(STDIN_FILENO, TCSANOW, &def_);
#elif _MSC_VER
    SetConsoleMode(handle_, mode_);
#endif
}
