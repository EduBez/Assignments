#include "stdafx.h"
#include "DataAccessLayer.h"

using namespace boost;
using namespace dal;
using namespace meta;
using namespace std;
using namespace types;

using namespace web::json;

//
//  DataAccessLayer
//
DataAccessLayer::DataAccessLayer()
{
    try
    {
        sql::SQLString addr = "tcp://localhost:3306";
        sql::SQLString user = "root";
        sql::SQLString pwd  = "root";

        driver_ = get_driver_instance();
        conn_ = driver_->connect(addr, user, pwd);

        // Use 'MachinesSystemInfo' database
        conn_->setSchema("MachinesSystemInfo");
    }
    catch (sql::SQLException& e)
    {
        conn_ = nullptr;
        wcout << e.what() << endl;
    }
}

void DataAccessLayer::AddMachine(const ClientInfo& client, bool update)
{
    try
    {
        // Build command
        string cmd = update ? BuildUpdateCmd(client) : BuildAddCmd(client);

        // Create SQL statement
        query_ = conn_->createStatement();

        // Execute query
        query_->execute(cmd.c_str());
    }
    catch (sql::SQLException& e) {
        wcout << e.what() << endl;
    }
}

bool DataAccessLayer::Authenticate(const std::string& key)
{
    return FindMachine(key);
}

string DataAccessLayer::BuildAddCmd(const ClientInfo& ci)
{
    // SQL command text
    string cmd = "INSERT INTO MachineRegistry VALUES "
        "('%1%', '%2%', '%3%', '%4%', '%5%')";

    // SQL command parameters
    cmd = boost::str(boost::format(cmd) % ci.key
                                        % ci.mail
                                        % ci.cpu
                                        % ci.memory
                                        % ci.processes);
    return cmd;
}

string DataAccessLayer::BuildGetCmd(const string& id)
{
    // SQL command text
    string cmd = "SELECT * FROM MachineRegistry WHERE MachineID = '%1%'";

    // SQL command parameters
    cmd = boost::str(boost::format(cmd) % id);
    return cmd;
}

string DataAccessLayer::BuildUpdateCmd(const ClientInfo& ci)
{
    // SQL command text
    string cmd = "UPDATE MachineRegistry SET Email='%1%', CpuLimit='%2%', "
        "MemoryLimit='%3%', ProcessesLimit='%4%' WHERE MachineID='%5%'";

    // SQL command parameters
    cmd = boost::str(boost::format(cmd) % ci.mail
                                        % ci.cpu
                                        % ci.memory
                                        % ci.processes
                                        % ci.key);
    return cmd;
}

bool DataAccessLayer::FindMachine(const std::string& id)
{
    bool result = false;

    try
    {
        // Build command
        string cmd = BuildGetCmd(id);

        // Create SQL statement
        query_ = conn_->createStatement();

        // Execute query
        recset_ = query_->executeQuery(cmd.c_str());

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

bool DataAccessLayer::Populate(const Machines& clients)
{
    // Verify if we have a valid database connection
    if (!conn_ || !conn_->isValid()) {
		return false;
	}

	for (auto const& mi : clients)
    {
        // Client NOT found
        if (!FindMachine(mi.key)) {
            // Add client info
            AddMachine(mi);
        }
        // Client found
        else {
            // Update client info
            AddMachine(mi, true);
        }
    }

    return true;
}

void DataAccessLayer::WMIAlert(const ClientInfo& info)
{
    try
    {
        // SQL command text
        string cmd = "INSERT INTO MachineUtilization VALUES "
            "('%1%', NOW(), '%2%', '%3%', '%4%', 1)";

        // SQL command parameters
        cmd = boost::str(boost::format(cmd) % info.key
                                            % info.memory
                                            % info.cpu
                                            % info.processes);
        // Create SQL statement
        query_ = conn_->createStatement();

        // Write alert to 'MachineUtilization' table
        query_->execute(cmd.c_str());
    }
    catch (sql::SQLException& e) {
        wcout << e.what() << endl;
    }
}

meta::ClientInfo DataAccessLayer::WMIThreshold(const string& key)
{
    ClientInfo result;

    try
    {
        if (FindMachine(key))
        {
            // Build command
            string cmd = BuildGetCmd(key);

            // Create SQL statement
            query_ = conn_->createStatement();

            // Execute query
            recset_ = query_->executeQuery(cmd.c_str());

            // Needed to fetch ROW into the result set
            recset_->next();

            // Retrieve COLUMN values
            string key  = ToStr(recset_->getString("MachineID"));
            string mail = ToStr(recset_->getString("Email"));

            string memory    = ToStr(recset_->getString("MemoryLimit"));
            string cpu       = ToStr(recset_->getString("CpuLimit"));
            string processes = ToStr(recset_->getString("ProcessesLimit"));

            result = {key, mail, memory, cpu, processes};
        }
    }
    catch (sql::SQLException& e) {
        wcout << e.what() << endl;
    }

    return result;
}
