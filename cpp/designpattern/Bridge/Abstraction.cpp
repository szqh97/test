#include "Abstraction.h"
#include "AbstractionImpl.h"
#include <iostream>

using namespace std;

Abstraction::Abstraction(){}
Abstraction::~Abstraction() {}

RefinedAbstraction::RefinedAbstraction(AbstractionImpl* impl)
{
    _impl = impl;
}

RefinedAbstraction::~RefinedAbstraction() {}

void RefinedAbstraction::Operation()
{
    _impl->Operation();
}
