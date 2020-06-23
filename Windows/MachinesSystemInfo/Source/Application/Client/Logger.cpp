#include "stdafx.h"
#include "Logger.h"

using namespace lgr;
using namespace std;

// Statics definition
std::wofstream Logger::log_;

//
//  Logger
//
Logger::~Logger()
{
    log_.close();
}

void Logger::Open(const std::wstring& file)
{
    log_.open(file.c_str()/*, std::ios::app*/);

    if (!log_.is_open())
    {
        string f(file.begin(), file.end());

        string msg = boost::str(boost::format
            ("Error opening log file: \"%1%\"") % f);

        throw std::runtime_error(msg);
    }
}
