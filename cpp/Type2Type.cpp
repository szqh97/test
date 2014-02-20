#include <iostream>
#include <string.h>
using namespace std;

template <class T, class U>
T* Create(const U& arg, T /* dummy */)
{
    return new T(arg);
}

template <class U>
int* Create(const U&arg, int /* dummy */)
{
    return new int(-1);
}

// Illegal code 
/* 
template <class U>
int* Create<int, U>(const U& arg)
{
    return new int(arg);
}
*/

template <typename T>
struct Type2Type
{
    typedef T OriginalType;
};

// An implementation of Create relying on overloading 
// and Type2Type
template <class T, class U>
T* create(const U& arg, Type2Type<T>)
{
    return new T(arg);
}

template<class U>
int* create(const U& arg, Type2Type<int>)
{
    return new int(arg);
}


int main ( int argc, char *argv[] )
{
    short s = 4;
    int *p= Create<short>(s, 4);
    cout << *p << endl;
    delete p;

    string* pstr = create("Hello", Type2Type<string>());
    cout << *pstr << endl;
    cout << * create(100, Type2Type<int>()) << endl;

    cout << sizeof(Type2Type<int>) << endl;

    return 0;
}			/* ----------  end of function main  ---------- */

