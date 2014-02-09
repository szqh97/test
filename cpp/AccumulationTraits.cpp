#include <iostream>
using namespace std;

template <class T> class AccumulationTraits;

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

template <typename T>
typename AccumulationTraits<T>::AccT accumulate(T const *begin, T const *end)
{
    typedef typename AccumulationTraits<T>::AccT AccT;
    AccT total = AccumulationTraits<T>::zero();
    while (begin != end)
    {
        total += *begin;
        ++begin;
    }
    return total;
}


int main ( int argc, char *argv[] )
{
    int test[5] = {1,2,3,4,5};
    char chartest[] = "template_test";
    int r = accumulate(test, test+5);
    int r2 = accumulate(chartest, chartest + sizeof(chartest));
    cout << " r is " << r << endl;
    cout << "r2 is " << r2 << endl;
    return 0;
}			/* ----------  end of function main  ---------- */
