#include "stdafx.h"
#include "JSONDataModule.h"

using namespace boost;
using namespace dml;
using namespace mtd;
using namespace std;
using namespace web::json;

//
//  JSONDataModule
//

// Ctor
JSONDataModule::JSONDataModule(mtd::Column column, std::wstring value)
    // Member Initialization List
    : column_ (column)
    , value_  (value)
{
    try
    {
        sql::SQLString addr = "tcp://localhost";
        sql::SQLString user = "root";
        sql::SQLString pwd  = "root";

        driver_ = get_driver_instance();
        conn_   = driver_->connect(addr, user, pwd);

        // Use 'NationalStolenVehicles' database
        conn_->setSchema("NationalStolenVehicles");
    }
    catch (sql::SQLException& e) {
        wcout << e.what() << endl;
    }
}

// Dtor
JSONDataModule::~JSONDataModule()
{
    conn_->close();
    // Cleanup
    delete recset_, query_, conn_;
}

void JSONDataModule::LogSearch()
{
    // Build SQL command
    wstring c = BuildLogCmd();

    // SQL connector only works with std::string 
    string cmd(c.begin(), c.end());

    // Log search
    query_->execute(cmd.c_str());
}

json_array_t JSONDataModule::FetchData()
{
    // Create an array of JSON values
    json_array_t recs;

    try
    {
        // Build SQL command
        wstring c = BuildQueryCmd();

        // SQL connector only works with std::string 
        string cmd(c.begin(), c.end());

        // Create SQL statement
        query_ = conn_ ->createStatement();

        // Execute query
        recset_ = query_->executeQuery(cmd.c_str());

        // Retrieve NOfRecs
        int recCount = recset_->rowsCount();

        // Records where found
        if (recCount != 0)
        {
            int id = 0;

            // While !EOf
            while (recset_->next())
            {
                web::json::value row = ParseRecord();

                auto key  = boost::lexical_cast<wstring>(id);
                auto pair = std::make_pair(key, row);

                recs.push_back(pair);

                // Increment id
                id += 1;
            }
        }

        // Log search
        LogSearch();
    }
    catch (sql::SQLException& e) {
        wcout << e.what() << endl;
    }

    return recs;
}

wstring JSONDataModule::BuildLogCmd()
{
    wstring col = DalMetaData::ColumnName(column_);

    // SQL command text
    wstring cmd = L"INSERT INTO VehicleSearchLog VALUES (0, '%1%', '%2%', NOW());";
    
    // SQL command paramenters
    cmd = boost::str(boost::wformat(cmd) % col % value_);
    return cmd;
}

wstring JSONDataModule::BuildQueryCmd()
{
    if (column_ == Column::ALL)
    {
        wstring cmd = L"SELECT * FROM StolenVehicles;";
        return cmd;
    }
    
    wstring col = DalMetaData::ColumnName(column_);

    // SQL command text
    wstring cmd = L"SELECT * FROM StolenVehicles WHERE %1% LIKE '%2%%%';";
    
    // SQL command parameters
    cmd = boost::str(boost::wformat(cmd) % col % value_);
    return cmd;
}

web::json::value JSONDataModule::ParseRecord()
{
    // RAW string literal
    wstring json =
        LR"({"Registration": "%1%", "Make": "%2%", "Model": "%3%", "Owner": "%4%"})";

    // Retrieve COLUMN values
    wstring c1 = S(recset_->getString("Registration"));
    wstring c2 = S(recset_->getString("Make"));
    wstring c3 = S(recset_->getString("Model"));
    wstring c4 = S(recset_->getString("Owner"));

    json = boost::str(boost::wformat(json) % c1 % c2 % c3 % c4);

    return web::json::value::parse(json);
}
