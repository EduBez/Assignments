#ifndef HemAnaGemHPP
    #define HemAnaGemHPP

#include "PreCompH.hpp"

namespace veus {

//
//  Automated Hematology Analyzer pseudo random generator
//
class HemAnaGen
{
    // Valid characters for a communication sequence
    inline static const std::string alfanum_ = "1234567890";

    // Length of each sequence indices
    static constexpr int length_ = 4;

    // Number of elements in a sequence
    static constexpr size_t pool_ = 5;

    // File name to store the sequence
    std::string file_;

public:
    // Ctor
    explicit HemAnaGen(std::string file) : file_(move(file)) {}

    // Member function
    void Generate();
};

}//EndOf namespace

#endif
