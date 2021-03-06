#include "StdAfx.h"

#include "HttpRequest.h"
#include "Maths.h"
#include "TypesDefs.h"

using namespace math;
using namespace std;
using namespace std::literals::string_literals;
using namespace types;
using namespace utility;// CppRestSDK

///////////////////////////////////////////////////////////////////////////////
//  GenerateStocks
//
VecPairStrFloat GenerateStocks(const VecStrings& symbols, int nOfquotes)
{
    // Default construct a 'random_device' and
    // call operator () to retrieve a seed number
    default_random_engine rng(random_device{}());

    VecPairStrFloat values;

    for (auto& symbol : symbols)
    {
        for (int i=0; i < nOfquotes; ++i)
        {
            float price = [&](){return (float)rng()*0.001;}();
            values.emplace_back(make_pair(symbol, price));
        }
    }
    return values;
}

///////////////////////////////////////////////////////////////////////////////
//  Main Entry Point
//
int main()
{
    VecStrings symbols{"ABC", "DEF", "GHI"};

    ///// Write to JSON files /////////////////////////////////////////////////

    for (int i=0; i < 3; ++i)
    {
        string file = "data" + to_string(i) + ".json";
        ofstream of(file);

        pt::ptree children;

        auto coll = GenerateStocks(symbols, 5);
        for (auto& c : coll)
        {
            pt::ptree child;

            child.put("price", c.second);
            child.put("symbol", c.first);

            children.push_back(make_pair("", child));
        }

        pt::ptree root;
        root.add_child("values", children);
        pt::write_json(of, root);
    }

    ///// Read from JSON files ////////////////////////////////////////////////

    MapStringFloat coll;

    for (int i=0; i < 3; ++i)
    {
        string file = "data" + to_string(i) + ".json";
        ifstream is(file);

        pt::ptree root;
        pt::read_json(is, root);

        for (auto& node : root.get_child("values"))
        {
            float value{};
            for (auto& cell : node.second)
            {
                if (cell.first == "price") {
                    value = stod(cell.second.data());
                }
                else if (cell.first == "symbol") {
                    coll.insert(make_pair(cell.second.data(), value));
                }
            }
        }
    }

    ///// Calculate median ////////////////////////////////////////////////////

    MapStringFloat median;

    for (auto& c : symbols)
    {
        auto range = coll.equal_range(c);

        float total{};
        for_each(range.first, range.second, [&](auto& it){total += it.second;});

        auto count = distance(range.first, range.second);
        median.insert(make_pair(range.first->first, total/count));
    }

    ///// Display results /////////////////////////////////////////////////////

    for (const auto& c : median) {cout << c.first << " average price = " << c.second << endl;}

    #if 0
    for_each(begin(median), end(median), [](const auto& c)
             {cout << c.first << " average price = " << c.second << endl;});

    transform(begin(median), end(median), ostream_iterator<string>(cout,""),
              [](const auto& c)
              {
                  ostringstream os;
                  os << c.first << " average price = " << c.second << endl;
                  return os.str();
              });
    #endif

    ///// Access REST endpoint ////////////////////////////////////////////////

    wstring data = Rest::HttpGet(L"http://api.football-data.org/v1/soccerseasons/424");

    stringstream stream;
    stream << string(begin(data), end(data));

    pt::ptree pt;
    pt::read_json(stream, pt);

    auto lu = pt.get<string>("lastUpdated");
    wstring date(begin(lu), end(lu));

    // ISO_8601 :: 2017-07-12T07:26:48Z
    auto dt = datetime::from_string(date, datetime::date_format::ISO_8601);
    auto ws =  dt.to_string();

    ////// Maths //////////////////////////////////////////////////////////////

    vector<float> vf{20.0f, 14.0f, 2.0f, 0.8f};
    auto mediam = Arithmetics::Median(vf);

    float wm = Arithmetics::WeightedMedian({20.0,14.0,2.0,0.8}, {1,1,12,6});

    // Dice :: number of possibilities to return and odd number
    // number of odd numbers = 3
    // sample space = 6

    float p = Arithmetics::Probability(3.0,6.0);

    int c = Arithmetics::Combinations(5,3);
    int a = Arithmetics::Arrangement(8,4);

    string s = "aba";
    sort(s.begin(), s.end());
    
    do {
        cout << s << '\n';
    } while (next_permutation(s.begin(), s.end()));

    return 0;
}
