#ifndef RdwDecoderHPP
    #define RdwDecoderHPP

#include "PreCompH.hpp"
#include "HemAnaGen.hpp"

namespace veus {

// Type alias
using VecStr = std::vector<std::string>;

//
//  RDW indices from a communication sequence 
//
struct RdwIndices 
{
    // ii => Integer part
    // ff => Fractional part
    // dd => Digit

    float  rdw_sd; // ii.ff
    int    mcv;    // dddd
    int    mchc;   // dddd
    int    mch;    // dddd
    float  rdw_cv; // ii.ff
};

//
//  Decodes a RDW data sequence
//
class RdwDecoder
{
    static constexpr int KEY_ENTER=10;
public:    
    static void Decode();
    static void Display(const RdwIndices& rdw);
    static RdwIndices Parse();
    static VecStr Split(const std::string& s, char delimiter);
};

}//EndOf namespace
#endif
