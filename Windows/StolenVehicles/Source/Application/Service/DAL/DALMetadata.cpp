#include "stdafx.h"
#include "DALMetadata.h"

using namespace mtd;
using namespace std;

//
//  DalMetaData
//
Column DalMetaData::ColumnID(std::wstring column)
{
    Column col;

    if (column == L"All")
        col = Column::ALL;

    else if (column == L"Registration")
        col = Column::REGISTRATION;

    else if (column == L"Make")
        col = Column::MAKE;

    else if (column == L"Model")
        col =  Column::MODEL;

    else if (column == L"Owner")
        col = Column::OWNER;

    return col;
}

wstring DalMetaData::ColumnName(Column column)
{
    wstring col;

    if (column == Column::ALL)
        col = L"All";

    else if (column == Column::REGISTRATION)
        col = L"Registration";

    else if (column == Column::MAKE)
        col = L"Make";

    else if (column == Column::MODEL)
        col = L"Model";

    else if (column == Column::OWNER)
        col = L"Owner";

    return col;
}
