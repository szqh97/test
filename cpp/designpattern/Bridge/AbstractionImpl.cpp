#include "AbstractionImpl.h"
#include <iostream>
using namespace std;

AbstractionImpl::AbstractionImpl(){}
AbstractionImpl::~AbstractionImpl() {}

void AbstractionImpl::Operation() 
{
    cout << "AbstractionImpl::Operation" << endl;
}

ConcreteAbstractionImplA::ConcreteAbstractionImplA() {}

ConcreteAbstractionImplA::~ConcreteAbstractionImplA(){}

void ConcreteAbstractionImplA::Operation()
{
    cout << "ConcreteAbstractionImplA::Operation" << endl;
}

ConcreteAbstractionImplB::ConcreteAbstractionImplB(){}

ConcreteAbstractionImplB::~ConcreteAbstractionImplB(){}

void ConcreteAbstractionImplB::Operation() 
{
    cout << "ConcreteAbstractionImplB::Operation()" << endl;
}

