#pragma once
#include "stdafx.h"

#include "Typedefs.h"

namespace evolve {
    namespace parser {

//
//  ConfigParser
//
struct ConfigParser
{
    // Member Function
    static types::Machines Parse();
}; 

}};//EndOf namespace

// Namespace alias
namespace parser = evolve::parser;
