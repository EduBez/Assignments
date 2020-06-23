#ifndef LOGGING_SYSTEM_HPP_INCLUDED
#define LOGGING_SYSTEM_HPP_INCLUDED

#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <exception>
#include <type_traits>

#include <boost/type_index.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <cpprest/http_msg.h>
#include <pplx/pplxtasks.h>

#include "Version.hpp"

#endif //LOGGING_SYSTEM_HPP_INCLUDED
