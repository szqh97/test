#ifndef _CHECKING_H_
#define _CHECKING_H_
#include <iostream>
template <class T> struct NoChecking
{
    static void Check(T*) {}
};

template <class T> struct EnforceNotNULL
{
    class NullPointerException: public std::exception {};
    static void CCheck(T* ptr)
    {
        if (!ptr) throw NullPointerException()
    }
};

template <class > struct EnsureNotNull
{
    static void Check(T*& ptr)
    {
        if (!ptr) ptr = GetDefaultValue();
    }
};
#endif
