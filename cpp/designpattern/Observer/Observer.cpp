#include "Observer.h"
#include <iostream>
using namespace std;
Observer::Observer()
{
    _st = '\0';
}
Observer::~Observer(){}

ConcreteObserverA::ConcreteObserverA(Subject* sub)
{
    _sub = sub;
    _sub->attach(this);
}

ConcreteObserverA::~ConcreteObserverA()
{
    _sub->detach(this);
    if (_sub)
    {
        delete _sub;
    }
}

Subject* ConcreteObserverA:: getSubject()
{
    return _sub;
}


void ConcreteObserverA::printInfo()
{
    cout << "ConcreteObserverA observer " << _sub->getState() << endl;
}

void ConcreteObserverA::update(Subject* s)
{
    _st = s->getState();
    printInfo();
}

ConcreteObserverB::ConcreteObserverB(Subject* sub)
{
    _sub = sub;
    _sub->attach(this);
}

ConcreteObserverB::~ConcreteObserverB()
{
    _sub->detach(this);
    if (_sub)
    {
        delete _sub;
    }
}

Subject* ConcreteObserverB:: getSubject()
{
    return _sub;
}


void ConcreteObserverB::printInfo()
{
    cout << "ConcreteObserverB observer " << _sub->getState() << endl;
}

void ConcreteObserverB::update(Subject* s)
{
    _st = s->getState();
    printInfo();
}


