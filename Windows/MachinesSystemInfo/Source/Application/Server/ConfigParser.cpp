#include "stdafx.h"

#include "Metadata.h"
#include "Typedefs.h"

#include "ConfigParser.h"

using namespace meta;
using namespace parser;
using namespace std;
using namespace types;

using boost::property_tree::ptree;

//
//  ConfigParser
//
Machines ConfigParser::Parse()
{
    // Collection to hold parsed XML content
    Machines mi;
    
    // Stream for XML file reading
    ifstream fs;

    try
    {
        fs.open("server.config.xml");

        // Populate tree structure
        ptree pt;
        read_xml(fs, pt);

        for (auto const& ref : pt.get_child("machines"))
        {
            if (ref.first == "client")
            {
                ClientInfo m;

                m.key       = ref.second.get<string>("key");
                m.mail      = ref.second.get<string>("mail");

                m.memory    = ref.second.get<string>("memory");
                m.cpu       = ref.second.get<string>("cpu");
                m.processes = ref.second.get<string>("processes");

                mi.push_back(m);
            }
        }
    }
    catch (exception& e) {
        wcout << e.what() << endl;
    }

    if (fs.is_open()) {
        fs.close();
    }

    return mi;
}
