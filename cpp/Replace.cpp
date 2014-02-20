#include <iostream>
//#include "Typelist.h"

using namespace std;

template <class Tlist, class T, class U> struct Replace;
template <class T, class U> struct Replace <NullType, T, U>
{
    typedef NullType Result;
};
template <class T, class Tail, class U>
struct Replace< Typelist<T,Tail>, T, U>
{
    typedef Typelist<U, Tail> Result;
};

template <class Head, class Tail, class T, class U>
struct Replace <Typelist<Head, Tail>, T, U>
{
    typedef Typelist<Head, 
            typename Replace<Tail, T, U>::Result >
        Result;
    

};

int main ( int argc, char *argv[] )
{
    typedef TYPELIST_3 (int, float, double) ifd;
    typedef Replace<ifd, int, char> cfd;

    return 0;
}			/* ----------  end of function main  ---------- */


