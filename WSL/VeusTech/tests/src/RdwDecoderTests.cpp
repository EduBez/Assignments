#include <gtest/gtest.h>

#include "HemAnaGen.hpp"
#include "PreCompH.hpp"
#include "RdwDecoder.hpp"
#include "StdCinUtil.hpp"

using namespace std;
using namespace veus;

namespace VeusTests {

//
//  Google Test Fixture Class
//
class Fixture : public ::testing::Test
{
protected:
    string file{"rdw_seq.dat"};

    void SetUp() override
    {
        HemAnaGen hag{file};
        hag.Generate();
    }

    void TearDown() override {
        remove(file.c_str());
    }
};

TEST_F(Fixture, HemAnaGenT)
{
    ifstream in{file};
    int count{0};
    string line{};

    for (int i=0; i < 5; ++i)
    {
        getline(in, line);
        count += 1;
    }
    ASSERT_EQ(count, 5);
}

TEST_F(Fixture, HemAnaGenT2)
{
    RdwIndices rdw{0,0,0,0,0};

    CinRedir redir{file};
    rdw = veus::RdwDecoder::Parse();

    ASSERT_NE(rdw.rdw_sd, 0);
    ASSERT_NE(rdw.mcv   , 0);
    ASSERT_NE(rdw.mchc  , 0);
    ASSERT_NE(rdw.mch   , 0);
    ASSERT_NE(rdw.rdw_cv, 0);
}

TEST(RdwDecoder, SliptT)
{
    string seq{R"(Veus^Technology)"};
    auto coll = veus::RdwDecoder::Split(seq, '^');

    ASSERT_EQ(coll.size(), 2);
}

TEST(RdwDecoder, SliptT2)
{
    string seq{R"(2710^1002^2105^9823^5387)"};
    auto coll = veus::RdwDecoder::Split(seq, '^');

    ASSERT_EQ(coll[0], string{"2710"});
    ASSERT_EQ(coll[1], string{"1002"});
    ASSERT_EQ(coll[2], string{"2105"});
    ASSERT_EQ(coll[3], string{"9823"});
    ASSERT_EQ(coll[4], string{"5387"});
}

TEST_F(Fixture, CinRedirT)
{
    CinRedir sir{file};

    string line{};
    getline(cin, line);

    ASSERT_EQ(line.size(), 25);
}

TEST_F(Fixture, CinRedirT2)
{
    CinRedir sir{file};

    string line{};
    getline(cin, line);

    auto counter = count(begin(line), end(line), '\r');
    ASSERT_EQ(counter, 5);
}

TEST_F(Fixture, CinRedirT3)
{
    CinRedir sir{file};

    string line{};
    getline(cin, line);

    auto lambda = [](auto ch){return isdigit(ch);};
    auto counter = count_if(begin(line), end(line), lambda);

    ASSERT_EQ(counter, 20);
}
}//EndOf namespace
