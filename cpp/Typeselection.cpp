#include <iostream>
using namespace std;
#if 0
template <typename T, bool isPolymorphic>
class NiftyContainerValueTraits
{
    typedef T* ValueType;
};

template <typename T>
struct NiftyContainerValueTraits<T, false>
{
    typedef T ValueType;
};

template <typename T, bool isPolymorphic>
class NiftyContainer
{
    typedef NiftyContainerValueTraits<T, isPolymorphic> Traits;
    typedef typename Traits::ValueType ValueType;

};

#endif
template <bool flag, typename T, typename U>
struct Select
{
    typedef T Result;
};

template <typename T, typename U>
struct Select<false, T, U>
{
    typedef U Result;
};

template <typename T, bool isPolymorphic>
class NiftyContainer
{
    public:
    typedef typename Select<isPolymorphic, T*, T>::Result ValueType;
    ValueType p;
};
int main ( int argc, char *argv[] )
{
    int i = 9;
    NiftyContainer<int, false> a;
    a.p = i;
    cout << a.p << endl;

    NiftyContainer<int, true> b;
    b.p = &i;
    cout << *(b.p) << endl;

    return 0;
}			/* ----------  end of function main  ---------- */
