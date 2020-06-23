#include "stdafx.h"
#include "JSONDataModule.h"

using namespace boost;
using namespace dal;
using namespace std;

using namespace web::json;

//
//  JSONDataModule
//
JSONDataModule::JSONDataModule()
{
    try
    {
        sql::SQLString addr = "tcp://localhost:3306";
        sql::SQLString user = "root";
        sql::SQLString pwd  = "root";

        driver_ = get_driver_instance();
        conn_ = driver_->connect(addr, user, pwd);

        // Use 'StockExchange' database
        conn_->setSchema("StockExchange");
    }
    catch (sql::SQLException& e)
    {
        conn_ = nullptr;
        wcout << e.what() << endl;
    }
}

bool JSONDataModule::Authenticate(const std::string& user,
                                  const std::string& pwd)
{
    bool result = false;

    try
    {
        // SQL command text
        string cmd = "SELECT * FROM Trader WHERE UserName = '%1%' AND Password = '%2%'";

        // SQL command parameters
        cmd = boost::str(boost::format(cmd) % user % pwd);

        // Create SQL statement
        stmt_ = conn_->createStatement();

        // Execute query
        recset_ = stmt_->executeQuery(cmd.c_str());

        // Retrieve record count
        auto nOfRecs = recset_->rowsCount();

        // Records where found
        result = (nOfRecs != 0);
    }
    catch (sql::SQLException& e) {
        wcout << e.what() << endl;
    }

    return result;
}

bool JSONDataModule::AddNewUser(const std::string& user,
                                const std::string& pwd)
{
    bool result = false;

    // User already exists
    if (Authenticate(user, pwd)) {
        return result;
    }

    try
    {
        // SQL command text
        string cmd = "INSERT INTO Trader VALUES (0, '%1%', '%2%', 100000.00)";

        // SQL command parameters
        cmd = boost::str(boost::format(cmd) % user % pwd);

        // Create SQL statement
        stmt_ = conn_->createStatement();

        // Execute query
        stmt_->execute(cmd.c_str());

        result = true;
    }
    catch (sql::SQLException& e) {
        wcout << e.what() << endl;
    }

    return result;
}

bool JSONDataModule::BuyStock(const std::string& user,
                              const std::string& pwd,
                              const std::string& stock,
                              const std::string& quantity,
                              const std::string& price)
{
    bool result = true;

    // User not found
    if (!Authenticate(user, pwd)) {
        return false;
    }

    try
    {
        // SQL command text
        string cmd = "CALL BuyStock ('%1%', '%2%', '%3%', %4%, %5%)";

        // SQL command parameters
        cmd = boost::str(boost::format(cmd) % user % pwd % stock % quantity % price);

        // Create SQL statement
        stmt_ = conn_->createStatement();

        // Execute StoredProc
        stmt_->execute(cmd.c_str());
    }
    catch (sql::SQLException& e)
    {
        result = false;
        wcout << e.what() << endl;
    }

    return result;
}

bool JSONDataModule::SellStock(const std::string& user,
                               const std::string& pwd,
                               const std::string& stock,
                               const std::string& quantity,
                               const std::string& price)
{
    bool result = true;

    // User not found
    if (!Authenticate(user, pwd)) {
        return false;
    }

    try
    {
        // SQL command text
        string cmd = "CALL SellStock ('%1%', '%2%', '%3%', %4%, %5%)";

        // SQL command parameters
        cmd = boost::str(boost::format(cmd) % user % pwd % stock % quantity % price);

        // Create SQL statement
        stmt_ = conn_->createStatement();

        // Execute StoredProc
        stmt_->execute(cmd.c_str());
    }
    catch (sql::SQLException& e)
    {
        result = false;
        wcout << e.what() << endl;
    }

    return result;
}

web::json::value JSONDataModule::GetStockCodes()
{
    web::json::value result;

    try
    {
        // SQL command text
        string cmd = "SELECT StockID FROM Stock ORDER BY StockID";

        // Create SQL statement
        stmt_ = conn_->createStatement();

        // Execute query
        recset_ = stmt_->executeQuery(cmd.c_str());

        // Retrieve NOfRecs
        int recCount = recset_->rowsCount();

        // Records where found
        if (recCount != 0)
        {
            int id = 0;

            // While !EOf
            while (recset_->next())
            {
               // Retrieve COLUMN value
                wstring code = S(recset_->getString("StockID"));

                result[id] = web::json::value::string(code);

                // Increment id
                id += 1;
            }
        }
    }
    catch (sql::SQLException& e) {
        wcout << e.what() << endl;
    }

    return result;
}

web::json::value JSONDataModule::GetStockQuote(const std::string& user,
                                               const std::string& pwd ,
                                               const std::string& code)
{
    web::json::value result;

    // User not found
    if (!Authenticate(user, pwd)) {
        return false;
    }

    try
    {
        // SQL command text
        string cmd = "SELECT * FROM Stock WHERE StockID = '%1%'";

        // SQL command parameters
        cmd = boost::str(boost::format(cmd) % code);

        // Create SQL statement
        stmt_ = conn_->createStatement();

        // Execute query
        recset_ = stmt_->executeQuery(cmd.c_str());

        // Must advance to fetch record set
        if (recset_->next())
        {
            wstring value = S(recset_->getString("LastSalePrice"));
            result = web::json::value::string(value);
        }
    }
    catch (sql::SQLException& e) {
        wcout << e.what() << endl;
    }

    return result;
}

web::json::value JSONDataModule::ViewPortfolio(const std::string& user,
                                               const std::string& pwd)
{
    web::json::value result;

    // User not found
    if (!Authenticate(user, pwd)) {
        return false;
    }

    try
    {
        // SQL command text
        string cmd = "CALL ViewPortfolio ('%1%', '%2%')";

        // SQL command parameters
        cmd = boost::str(boost::format(cmd) % user % pwd);

        // Create SQL statement
        stmt_ = conn_->createStatement();

        // Execute StoredProc
        stmt_->execute(cmd.c_str());

        // Create an array of JSON values
        web::json::value rows;

        // Index into JSON array
        int id = 0;

        // Fetch record set
        recset_ = stmt_->getResultSet();

        while (recset_->next())
        {
            web::json::value row;

            row [L"TraderID"     ] = web::json::value(S(recset_->getString("TraderID")));
            row [L"StockID"      ] = web::json::value(S(recset_->getString("StockID")));
            row [L"CompanyName"  ] = web::json::value(S(recset_->getString("CompanyName")));
            row [L"Quantity"     ] = web::json::value(S(recset_->getString("Quantity")));
            row [L"TotalCost"    ] = web::json::value(S(recset_->getString("TotalCost")));
            row [L"LastSalePrice"] = web::json::value(S(recset_->getString("LastSalePrice")));

            rows[id] = row;

            // Increment id
            id += 1;
        }

        result[L"Portfolio"] = rows;
    }
    catch (sql::SQLException& e) {
        wcout << e.what() << endl;
    }

    return result;
}

web::json::value JSONDataModule::ViewTransactions (const std::string& user,
                                                   const std::string& pwd)
{
    web::json::value result;

    // User not found
    if (!Authenticate(user, pwd)) {
        return false;
    }

    try
    {
        // SQL command text
        string cmd = "CALL ViewTransactions ('%1%', '%2%')";

        // SQL command parameters
        cmd = boost::str(boost::format(cmd) % user % pwd);

        // Create SQL statement
        stmt_ = conn_->createStatement();

        // Execute StoredProc
        stmt_->execute(cmd.c_str());

        // Create an array of JSON values
        web::json::value rows;

        // Index into JSON array
        int id = 0;

        // Fetch record set
        recset_ = stmt_->getResultSet();

        while (recset_->next())
        {
            web::json::value row;

            row [L"TraderID" ] = web::json::value(S(recset_->getString("TraderID")));
            row [L"StockID"  ] = web::json::value(S(recset_->getString("StockID")));
            row [L"Quantity" ] = web::json::value(S(recset_->getString("Quantity")));
            row [L"DateTime" ] = web::json::value(S(recset_->getString("DateTime")));
            row [L"Operation"] = web::json::value(S(recset_->getString("Operation")));
            row [L"Status"   ] = web::json::value(S(recset_->getString("Status")));

            rows[id] = row;

            // Increment id
            id += 1;
        }

        result[L"Transactions"] = rows;
    }
    catch (sql::SQLException& e) {
        wcout << e.what() << endl;
    }

    return result;
}
