#pragma once
#include "stdafx.h"

#include "DALMetadata.h"
#include "JSONDataModule.h"

namespace Evolve {
    namespace Dal {

//
//  DataAccessLayer
//
class DataAccessLayer
{
public:
    // Data Members
    dml::json_array_t Query(mtd::Column column, std::wstring value);
};

}};//EndOf namespace
// Namespace alias
namespace dal = Evolve::Dal;
