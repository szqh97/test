#ifndef __TYPELLIST_H_
#define __TYPELIST_H_

struct NullType;
template <class T, class U>
struct Typelist
{
    typedef T Head;
    typedef U Tail;
};

#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4) >
#define TYPELIST_5(T1, T2, T3, T4, T5) Typelist<T1, TYPELIST_4(T2, T3, T4, T5) >

template <class Tlist> struct Length;
template <>struct Length<NullType>
{
    enum { value = 0};
};

template <class T, class U>
struct Length<Typelist<T, U> >
{
    enum {value = 1 + Length<U>::value};
};

// TypeAt :
template <class Tlist, unsigned int index> struct TypeAt;
template <class Head, class Tail>
struct TypeAt<Typelist<Head, Tail>, 0 >
{
    typedef Head Result;
};

template <class Head, class Tail, unsigned int i>
struct TypeAt<Typelist<Head, Tail>, i>
{
    typedef typename TypeAt<Tail, i-1>::Result Result;
};

// Index of type
template <class TList, class T> struct IndexOf;

template <class T>
struct IndexOf<NullType, T>
{
    enum {value = -1};
};

template <class Tail, class T>
struct IndexOf<Typelist<T,Tail>, T>
{
    enum {value = 0};
};

template <class Head, class Tail, class T>
struct IndexOf<Typelist<Head, Tail>, T>
{
    private:
        enum {temp = IndexOf<Tail, T>::value};
    public:
        enum {value = temp == -1? -1 : 1 + temp};
};
  
// Append
template <class Tlist, class T> struct Append;

template <> struct Append<NullType, NullType>
{
    typedef NullType Result;
};

template <class T> struct Append<NullType, T>
{
    typedef TYPELIST_1(T) Result;
};

template <class Head, class Tail> 
struct Append <NullType, Typelist<Head, Tail> >
{
    typedef Typelist<Head, Tail> Result;
};

template <class Head, class Tail, class T>
struct Append<Typelist<Head, Tail>, T >
{
    typedef Typelist<Head, 
            typename Append<Tail, T>::Result > Result;
};

// Erase
template <class Tlist, class T> struct Erase;

template <class T>
struct Erase<NullType, T>
{
    typedef NullType Result;
};

template <class T, class Tail>
struct Erase<Typelist<T, Tail>, T>
{
    typedef Tail Result;
};

template <class Head, class Tail, class T>
struct Erase<Typelist<Head, Tail>, T>
{
    typedef Typelist<Head, 
            typename Erase<Tail, T>::Result >
        Result;

};

// EraseAll
template <class Tlist, class T> struct EraseAll;

template <class T>
struct EraseAll <NullType, T>
{
    typedef NullType Result;
};

template <class T, class Tail>
struct EraseAll<Typelist<T, Tail>, T>
{
    //Go all the way down the list removint the type
    typedef typename EraseAll<Tail, T>::Result Result;
};

template <class Head, class Tail, class T>
struct EraseAll<Typelist<Head, Tail>, T>
{
    //Go all the way down the list removint the type
    typedef Typelist<Head, 
            typename EraseAll<Tail, T>::Result>
        Result;
};

// NoDuplicates
template <class Tlist> struct NoDuplicates;
template <> struct NoDuplicates<NullType>
{
    typedef NullType Result;
};

template <class Head, class Tail>
struct NoDuplicates<Typelist<Head, Tail> >
{
private:
    typedef typename NoDuplicates<Tail>::Result L1;
    typedef typename Erase<L1, Head>::Result L2;
public:
    typedef Typelist<Head, L2> Result;
};

#endif
