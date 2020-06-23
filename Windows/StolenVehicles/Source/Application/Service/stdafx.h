#pragma once
#include "targetver.h"

#include <Windows.h>
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <tchar.h>

// STL
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

// Boost
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

// C++ REST SDK
#include <cpprest/containerstream.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/producerconsumerstream.h>

// MySQL C++ Connector
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
