#include "StdAfx.h"
#include "JsonUnit.h"

using namespace std;
using namespace types;

///////////////////////////////////////////////////////////////////////////////
//   DataPoints
//
DataPoints::DataPoints(const string& file)
{
    pt::read_json(file, root);
}

VecPairStrings DataPoints::GetAnimals()
{
    vector<PairStrings> animals;
    for (pt::ptree::value_type& animal : root.get_child("animals"))
    {
        string name = animal.first;// Get the label of the node
        string color = animal.second.data();// Get the content of the node
        animals.emplace_back(make_pair(name, color));
    }
    return animals;
}

string DataPoints::GetComplexPath(const string& path)
{
    return root.get<string>(path);
}

VecStrings DataPoints::GetFruits()
{
    VecStrings fruits;
    for (pt::ptree::value_type& fruit : root.get_child("fruits"))
    {
        // fruit.first contain the string ""
        // or use 'fruit.second.get_value<string>();'
        fruits.emplace_back(fruit.second.data());
    }
    return fruits;
}

int DataPoints::GetHeight()
{
    return root.get<int>("height", 0);
}

Matrix DataPoints::GetMatrix()
{
    Matrix mtx(3,3);

    int x = 0;
    for (pt::ptree::value_type& row : root.get_child("matrix"))
    {
        int y = 0;
        for (pt::ptree::value_type& cell : row.second)
        {
            mtx(x,y) = cell.second.get_value<int>();
            y++;
        }
        x++;
    }
    return mtx;
}
