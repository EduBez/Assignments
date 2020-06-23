#pragma once
#include "TypesDefs.h"

///////////////////////////////////////////////////////////////////////////////
//   DataPoints
//
class DataPoints
{
    pt::ptree root;// Create a root
public:
    // Ctor
    DataPoints(const std::string& file);

    types::VecPairStrings GetAnimals();
    std::string           GetComplexPath(const std::string& path);
    types::VecStrings     GetFruits();
    int                   GetHeight();
    types::Matrix         GetMatrix();
};
