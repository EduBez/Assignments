#include "stdafx.h"
#include "DataAccessLayer.h"

using namespace boost;
using namespace dal;
using namespace dml;
using namespace mtd;
using namespace std;
using namespace web::json;

//
//  DataAccessLayer
//
json_array_t DataAccessLayer::Query(Column column, wstring value)
{
    json_array_t recs;

    // Instantiate the data module
    dml::JSONDataModule dm(column, value);

    // Fetch values from database
    recs = dm.FetchData();

    return recs;
}
