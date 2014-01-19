#include <iostream>
using namespace std;
template <typename InIt, typename OutIt>
OutIt Copy(InIt first, InIt last, OutIt result)
{
    for (; first != last; ++first, ++result)
        *result = *first;
}

struct NullType;
struct EmptyType {};
template <typename T>
class TypeTraits
{
    private:
        template <class U> struct PointerTraits
        {
            enum { result = false};
            typedef NullType PointeeType;
        };
        template <class U> struct PointerTraits<U*>
        {
            enum {result = true};
            typedef U PointeeType;
        };
    public:
        enum {isPointer = PointerTraits<T>::result };
        typedef typename PointerTraits<T>::PointeeType PointeeType;

};


int main ( int argc, char *argv[] )
{
    TypeTraits<int* > a;
    cout << a.isPointer << endl;

    TypeTraits<int> b;
    cout << a.isPointer << endl;
    return 0;
}			/* ----------  end of function main  ---------- */
