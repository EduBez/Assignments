#pragma once

#include <initializer_list>
#include <numeric>
#include <type_traits>

namespace math {

///////////////////////////////////////////////////////////////////////////////
//   Arithmetics
//
class Arithmetics
{
    template <typename T, typename C=std::vector<T>>
    static auto IotaColl(T size)
    {
        C coll(size);
        std::iota(std::begin(coll), std::end(coll), 1);
        return coll;
    }

public:    
    template <typename T, typename U>
    static auto WeightedMedian(std::initializer_list<U> Values,
                               std::initializer_list<T> Weights)
    {
        static_assert(std::is_arithmetic_v<T> && std::is_arithmetic_v<U>);

        if (Values.size() != Weights.size()) return U{};
        
        std::vector<U> transformed(Values.size());

        std::transform(begin(Values), end(Values), // range of the 'First' sequence
                       begin(Weights),             // begin of the 'Second' sequence
                       begin(transformed),         // begin of the 'Result' sequence 
                       std::multiplies<U>());      // binary operation to apply

        U sumT = std::accumulate(begin(transformed), end(transformed), U{});
        U sumW = std::accumulate(begin(Weights), end(Weights), U{});

        return sumT/sumW;
    }

    template <typename T>
    static auto Median(const T& Values)
    {
        using ValType = typename T::value_type;
        static_assert(std::is_arithmetic_v<ValType>);

        auto sum = std::accumulate(std::begin(Values), std::end(Values), ValType{});
        return sum/Values.size();
    }

    static auto Combinations(int NoOfElems, int SubsetSize)
    {
        auto v1 = IotaColl(NoOfElems);
        auto v2 = IotaColl(SubsetSize);
        auto v3 = IotaColl(NoOfElems-SubsetSize);

        int e = std::accumulate(begin(v1), end(v1), 1,
                                std::multiplies<int>());

        int s = std::accumulate(begin(v2), end(v2), 1,
                                std::multiplies<int>());

        int r = std::accumulate(begin(v3), end(v3), 1,
                                std::multiplies<int>());
        return e/(s*r);
    }

    static auto Arrangement(int NoOfElems, int SubsetSize)
    {
        auto v1 = IotaColl(NoOfElems);
        auto v2 = IotaColl(NoOfElems-SubsetSize);

        int e = std::accumulate(begin(v1), end(v1), 1,
                                std::multiplies<int>());

        int r = std::accumulate(begin(v2), end(v2), 1,
                                std::multiplies<int>());
        return e/r;
    }

    static auto Probability(float Possibility, float SampleSpace)
    {
        return Possibility/SampleSpace;
    }
};
 
}// EndOf namespace
