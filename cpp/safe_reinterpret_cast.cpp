#include <iostream>
#include <assert.h>
using namespace std;

template <class To, class From>
To safe_reinterpret_cast(From from)
{
    assert(sizeof(From) <= sizeof(To));
    cout << sizeof (From) << ", " << sizeof(To) << endl;
    return reinterpret_cast<To>(from);
}
struct A
{
    int a;
};
struct B
{
    int b;
    int a;
};
//
//partial template specilazation
template <bool> struct CompileTimeError;
template <> struct CompileTimeError<true> {};
#define STATIC_CHECK(expr) (CompileTimeError<(expr) != 0>())

template <bool> struct CompileTimeChecker
{
    CompileTimeChecker(...);
};

template <> struct CompileTimeChecker<false> {};
#define STATIC_CHECKER(expr, msg)\
{\
    class ERROR_##msg {};\
    (void) sizeof(CompileTimeChecker<(expr) > (ERROR_##msg())); \
}
int main ( int argc, char *argv[] )
{
    //STATIC_CHECK(0);
    STATIC_CHECKER(1, Destination_Type_Too_Narrow);

//short p = safe_reinterpret_cast<short>(a);
    return 0;
}			/* ----------  end of function main  ---------- */
