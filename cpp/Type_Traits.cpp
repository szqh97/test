#include <iostream>
#include <vector>
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

        template <class U> struct PToMTraits
        {
            enum { result = false };
        };
        template <class U, class V >
        struct PToMTraits<U V::*>
        {
            enum { result = true };
        };
    public:
        enum {isPointer = PointerTraits<T>::result };
        enum {isMemberPointer = PToMTraits<T>::result };
        typedef typename PointerTraits<T>::PointeeType PointeeType;

};


int main ( int argc, char *argv[] )
{
class A{
    public:
    typedef int Int;
    int a;
    int* p;
};
A k;
cout << TypeTraits<A::Int>::isMemberPointer << endl;
    const bool iterIsPtr = 
        TypeTraits<vector<int>::iterator>::isPointer;
    cout << iterIsPtr << endl;
    //cout << "vector<int>::iterator is " << iterIsPtr ? "fast" : "smart" << endl;
    TypeTraits<int* > a;
    cout << a.isPointer << endl;

    TypeTraits<int> b;
    cout << a.isPointer << endl;
    return 0;
}			/* ----------  end of function main  ---------- */
