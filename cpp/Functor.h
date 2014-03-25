#ifndef __FUNCTOR_H_
#define __FUNCTOR_H_
#include "Typelist.h"
#include <iostream>
#include <memory>
#if 0
template <typename ResultType>
class Functor
{
public:
    ResultType operator()();
private:
};

#endif
template <typename R, class Tlist>
class FunctorImpl;

template <typename R>
class FunctorImpl<R, NullType>
{
public:
    virtual R operator()() = 0;
    virtual FunctorImpl* Clone() const = 0;
    virtual ~FunctorImpl(){}
};

template <typename R, typename P1>
class FunctorImpl<R, TYPELIST_1(P1)>
{
public:
    virtual R operator()(P1) = 0;
    virtual FunctorImpl* Clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename R, typename P1, typename P2>
class FunctorImpl<R, TYPELIST_2(P1,P2)>
{
public:
    virtual R operator() (P1, P2) = 0;
    virtual FunctorImpl* Clone() const = 0;
    virtual ~FunctorImpl() {}
};

template <typename R, class TList>
class Functor
{

private:
    typedef FunctorImpl<R, TList> Impl;
public:
    Functor();
    Functor(const Functor&);
    Functor& operator=(const Functor&);
    explicit Functor(std::auto_ptr<Impl> spImpl_);
    std::auto_ptr<Impl> spImpl_;
};
#endif
