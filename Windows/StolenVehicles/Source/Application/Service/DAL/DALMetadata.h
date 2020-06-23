#pragma once
#include "stdafx.h"

namespace Evolve {
    namespace Mtd {

//
//  Column
//
enum class Column
{
    // Represents table column names
      NONE
    , ALL
    , REGISTRATION
    , MAKE
    , MODEL
    , OWNER
}; 

//
//  DalMetaData
//
struct DalMetaData
{
    static Column       ColumnID   (std::wstring column);
    static std::wstring ColumnName (Column column);
};

}};//EndOf namespace
// Namespace alias
namespace mtd = Evolve::Mtd;
