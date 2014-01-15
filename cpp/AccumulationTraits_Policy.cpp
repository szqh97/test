#include <iostream>
using namespace std;

template <typename T> class AccumulationTraits;

template <> 
class AccumulationTraits<char>
{
    public:
        typedef int AccT;
        static AccT zero() {return 0;}
};

template <>
class AccumulationTraits<int>
{
    public:
        typedef long long AccT;
        static AccT zero() {return 0;}
};

template <>
class AccumulationTraits<unsigned int>
{
    public:
        typedef unsigned long long AccT;
        static AccT zero() {return 0;}
};

template <>
class AccumulationTraits<float>
{
    public:
        typedef double AccT;
        static AccT zero() {return 0;}
};

template <typename T1, typename T2>
class SumPolicy
{
public:
    //template <typename T1, typename T2>
    static void accumulate (T1& total, T2 const &value)
    {
        total += value;
    }
};

template <typename T1, typename T2>
class MultiPolicy
{
public:
    //template <typename T1, typename T2>
    static void accumulate(T1& total, T2 const &value)
    {
        total *= value;
    }

};

//template <typename T, typename Policy = SumPolicy, typename Traits = AccumulationTraits<T> >
template <typename T, template <typename T1, typename T2> class Policy = SumPolicy, typename  Traits = AccumulationTraits<T> >
class Accum
{
public:
    typedef typename Traits::AccT AccT;
    static AccT accumulate(T const *begin, T const *end)
    {
        AccT total = Traits::zero();
        while (begin != end)
        {
            // template function
            //Policy::accumulate(total, *begin);
            Policy<AccT, AccT>::accumulate(total, *begin);
            ++begin;
        }
        return total;
    }

};


int main ( int argc, char *argv[] )
{
    int test[5] = {1,2,3,4,5};
    int r = Accum<int, MultiPolicy>::accumulate(test, test + 5);
    cout << " r is " << r << endl;
    return 0;
}			/* ----------  end of function main  ---------- */
