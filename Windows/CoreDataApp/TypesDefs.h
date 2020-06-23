#pragma once
#include "StdAfx.h"

namespace bnu = boost::numeric::ublas;
namespace pt  = boost::property_tree;

// Begin Of namespace
namespace types {

using Matrix = bnu::matrix<int>;

using MapStringFloat  = std::multimap<std::string, float>;
using PairStrings     = std::pair<std::string, std::string>;
using PairStrFloat    = std::pair<std::string, float>;
using VecPairStrFloat = std::vector<PairStrFloat>;
using VecPairStrings  = std::vector<PairStrings>;
using VecStrings      = std::vector<std::string>;

}//End Of namespace
