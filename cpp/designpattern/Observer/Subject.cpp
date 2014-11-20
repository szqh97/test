#include "Subject.h"
Subject::Subject()
{
    _obvs = new list<Observer*>;
}

Subject::~Subject()
{
    list<Observer*>::iterator it ;
    for (it = _obvs->begin(); it != _obvs->end(); ++it)
    {
        delete (*it);
    }
    delete _obvs;
}

void Subject::attach(Observer* obs)
{
    _obvs->push_front(obs);
}

void Subject::detach(Observer* obs)
{
    if (_obvs)
    {
        _obvs->remove(obs);
    }
}

void Subject::notify()
{
    list<Observer*>::iterator it; 
    for (it = _obvs->begin(); it != _obvs->end(); ++it)
    {
    
        (*it)->update(this);
    }
}

ConcreteSubject::ConcreteSubject()
{
    _st = '\0';
}

ConcreteSubject::~ConcreteSubject()
{
}

State ConcreteSubject::getState()
{
    return _st;
}

void ConcreteSubject::setState(const State& s)
{
    _st = s;
}



