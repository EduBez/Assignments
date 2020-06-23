#pragma once
#include "stdafx.h"

#include "DALMetadata.h"

namespace Evolve {
    namespace Dml {

// Type Aliases
using json_value_t = std::pair<std::wstring, web::json::value>;
using json_array_t = std::vector<json_value_t>;

//
//  JSONDataModule
//
class JSONDataModule
{
    // Data Members
    mtd::Column  column_;
    std::wstring value_;

    sql::Driver     *driver_;
    sql::Connection *conn_;
    sql::Statement  *query_;
    sql::ResultSet  *recset_;

    // Convert from 'SQLString' to 'std::wstring'
    inline std::wstring S(const sql::SQLString& s)
    {
        std::string w(s.c_str());
        return std::wstring(w.begin(), w.end());
    };

    void LogSearch();

    // Parse result set into JSON
    web::json::value ParseRecord();

    // SQL commands build
    std::wstring BuildLogCmd   ();
    std::wstring BuildQueryCmd ();

public:
    // Ctor
    JSONDataModule(mtd::Column column, std::wstring value);

    // Dtor
    ~JSONDataModule();

    // Member Functions
    json_array_t FetchData();
};

}};//EndOf namespace
// Namespace alias
namespace dml = Evolve::Dml;
