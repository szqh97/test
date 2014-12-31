#include "Handle.h"
#include <iostream>
using namespace std;
Handle::~Handle()
{
    delete _succ;
}

Handle::Handle(Handle* succ)
{
    this->_succ = succ;
}

void Handle::setSuccessor(Handle* succ)
{
    this->_succ = succ;
}

Handle* Handle::getSuccessor()
{
    return this->_succ;
}

ConcreteHandleA::ConcreteHandleA(Handle* succ):Handle(succ){}

ConcreteHandleA::~ConcreteHandleA(){}

void ConcreteHandleA::HandleRequest()
{
    if (this->getSuccessor() )
    {
        cout << "pass request to others" << endl;
        this->getSuccessor()->HandleRequest();
    }
    else
    {
        cout << "ConcreteHandleA request" << endl;
    }
}

ConcreteHandleB::ConcreteHandleB(Handle* succ):Handle(succ){}

ConcreteHandleB::~ConcreteHandleB(){}

void ConcreteHandleB::HandleRequest()
{
    if (this->getSuccessor() )
    {
        cout << "pass request to others" << endl;
        this->getSuccessor()->HandleRequest();
    }
    else
    {
        cout << "ConcreteHandleB request" << endl;
    }
}

