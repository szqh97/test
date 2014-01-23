#ifndef __TYPELLIST_H_
#define __TYPELIST_H_

struct NullType;
template <class T, class U>
struct Typelist
{
    typedef T Head;
    typedef U Tail;
};

typedef Typelist<char, Typelist<signed char, unsigned char > > CharList;
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4) >

#endif
