#pragma once
#include "stdafx.h"

namespace evolve {
    namespace smtp {

//
//  SMTP
//
class SMTP : private boost::noncopyable
{
    unsigned port_;

    std::string server_;
    std::string username_;
    std::string password_;

public:
    // Ctor
    SMTP(std::string server,
         unsigned    port,
         std::string user,
         std::string password);

    // Member Function
    bool Send(std::string from,
              std::string to,
              std::string subject,
              std::string message);
}; 

}};//EndOf namespace

// Namespace alias
namespace smtp = evolve::smtp;
