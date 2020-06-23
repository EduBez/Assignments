#pragma once
#include <cpprest/json.h>

namespace evolve {
    namespace meta {

//
//  ClientInfo
//
struct ClientInfo
{
    std::string key;
    std::string mail;
    std::string memory;
    std::string cpu;
    std::string processes;
};

}};//EndOf namespace

// Namespace alias
namespace meta = evolve::meta;
