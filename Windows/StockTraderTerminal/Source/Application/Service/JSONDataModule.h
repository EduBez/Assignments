#pragma once
#include "stdafx.h"

namespace evolve {
    namespace dal {

//
//  JSONDataModule
//
class JSONDataModule
{
    // Data Members
    sql::Driver     *driver_;
    sql::Connection *conn_  ;
    sql::Statement  *stmt_  ;
    sql::ResultSet  *recset_;

public:
    // Ctor
    JSONDataModule();

    // Convert from 'SQLString' to 'std::wstring'
    inline std::wstring S(const sql::SQLString& s)
    {
        std::string w(s.c_str());
        return std::wstring(w.begin(), w.end());
    };

    // Member Functions
    bool Authenticate (const std::string& user,
                       const std::string& pwd);

    bool AddNewUser   (const std::string& user,
                       const std::string& pwd);

    bool BuyStock     (const std::string& user,
                       const std::string& pwd,
                       const std::string& stock,
                       const std::string& quantity,
                       const std::string& price);

    bool SellStock    (const std::string& user,
                       const std::string& pwd,
                       const std::string& stock,
                       const std::string& quantity,
                       const std::string& price);

    web::json::value GetStockCodes    ();

    web::json::value GetStockQuote    (const std::string& user,
                                       const std::string& pwd ,
                                       const std::string& code);

    web::json::value ViewPortfolio    (const std::string& user,
                                       const std::string& pwd);

    web::json::value ViewTransactions (const std::string& user,
                                       const std::string& pwd);
};

}};//EndOf namespace
// Namespace alias
namespace dal = evolve::dal;
