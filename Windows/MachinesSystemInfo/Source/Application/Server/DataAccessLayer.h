#pragma once
#include "stdafx.h"

#include "Metadata.h"
#include "Typedefs.h"

#include "ConfigParser.h"

namespace evolve {
    namespace dal {

//
//  DataAccessLayer
//
class DataAccessLayer : private boost::noncopyable
{
    // Data Members
    sql::Driver     *driver_;
    sql::Connection *conn_;
    sql::Statement  *query_;
    sql::ResultSet  *recset_;

    // Member Functions
    inline std::string ToStr(sql::SQLString& sqlstr)
        { return std::string(sqlstr.c_str()); }

    void        AddMachine      (const meta::ClientInfo& ci,
                                 bool update=false);
    
    std::string BuildAddCmd     (const meta::ClientInfo& ci);

    std::string BuildGetCmd     (const std::string& id);

    std::string BuildUpdateCmd  (const meta::ClientInfo& ci);

    bool        FindMachine     (const std::string& id);

public:
    // Ctor
    DataAccessLayer();

    // Member Functions
    bool             Authenticate  (const std::string& key);

    void             WMIAlert      (const meta::ClientInfo& info);

    meta::ClientInfo WMIThreshold  (const std::string& key);

    bool             Populate      (const types::Machines& clients);
};

}};//EndOf namespace
// Namespace alias
namespace dal = evolve::dal;
