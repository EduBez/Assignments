#include "RdwDecoder.hpp"
#include "StdCinUtil.hpp"

using namespace std;
using namespace veus;

//
//  Decodes a RDW data sequence
//
void RdwDecoder::Decode()
{
    bool running{true};

    // Background thread to control program lifetime
    // Will terminate on user imputing 'ENTER'
    thread end_run {[&running](){
        CinEchOff echo{};int c{0};do {c=getchar();} while (c != KEY_ENTER);running=false;}
    };

    // File name that will store generated RDW sequence
    const std::string file{"hematology_analyzer.dat"};

    while (running)
    {
        // Start the Automated Hematology Analyzer random generator
        HemAnaGen hag{file};
        hag.Generate();

        // Redirects 'cin' to read from file
        CinRedir sir{file};

        // Extract and parse RDW sequence
        RdwIndices rdw = Parse();

        // Display the RDW sequence
        Display(rdw);

        remove(file.c_str());
    }
    end_run.join();
}

void RdwDecoder::Display(const RdwIndices& rdw)
{
    cout << "RDWCV="
         << fixed << setw(4) << setprecision(1) << setfill('0') << rdw.rdw_cv
         << ", "
         << "RDWSD="
         << fixed << setw(4) << setprecision(1) << setfill('0') << rdw.rdw_sd
         << endl;
}

RdwIndices RdwDecoder::Parse()
{
    RdwIndices rdw{0,0,0,0,0};
    string line{};

    // A sequence is composed of 5 elements
    while (getline(cin, line))
    {
        auto ids = Split(line, '\r');

        ids[0] = ids[0].insert(2, 1, '.');
        ids[4] = ids[4].insert(2, 1, '.');

        // The less significant fractional digit must be discarded
        // Floating point value will be truncated
        ids[0].at(4) = '0';
        ids[4].at(4) = '0';

        rdw.rdw_sd = std::stof(ids[0]);
        rdw.mcv    = std::stoi(ids[1]);
        rdw.mchc   = std::stoi(ids[2]);
        rdw.mch    = std::stoi(ids[3]);
        rdw.rdw_cv = std::stof(ids[4]);
    }
    return rdw;
}

VecStr RdwDecoder::Split(const string& s, char delimiter)
{
    VecStr tokens{};
    string token{};
    istringstream stream{s};

    while (getline(stream, token, delimiter)) {
        tokens.emplace_back(token);
    }
    return tokens;
}
