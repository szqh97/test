#include <iostream>
#include <vector>
using namespace std;

template <class T, class U>
class Conversion
{
    typedef char Small;
    class Big { char dummy[2];};
    static Small Test(U);
    static Big Test(...);
    static T MakeT();
public:
    enum { exists  = 
            sizeof(Test(MakeT())) == sizeof(Small) };
    enum { exists2Way = exists && Conversion<U, T>::exists };
    enum { sameType = false};
};

template <class T>
class Conversion<T, T>
{
    public:
        enum {exists = 1, exists2Way = 1, sameType = 1};
};

#define SUPERSUBCLASS(T, U) \
    (Conversion<const U*, const T*>::exists && \
     !Conversion<const T*, const void*>::sameType)
#define SUPERSUBCLASS_STRICT(T, U)\
    (SUPERSUBCLASS(T,U) && \
     !Conversion<const T, const U>::sameType)

int main ( int argc, char *argv[] )
{
    int a =1;
    char b = 'c';
    cout << SUPERSUBCLASS(int, char) << endl;
    cout << SUPERSUBCLASS(char, char) << endl;
    cout << SUPERSUBCLASS_STRICT(int, char) << endl;
    cout << SUPERSUBCLASS_STRICT(char, char) << endl;
    cout << SUPERSUBCLASS_STRICT(char,int ) << endl;
#if 0
    cout << Conversion<double, int>::exists << " " 
        << Conversion<char, char*>::exists << " "
        << Conversion<size_t, vector<int> >::exists << endl;
#endif
    return 0;
}			/* ----------  end of function main  ---------- */
