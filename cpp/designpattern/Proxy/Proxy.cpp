#include "Proxy.h"
#include <iostream>
using namespace std;

Subject::Subject(){}

Subject::~Subject(){}

ConcreteSubject::ConcreteSubject(){}
 
ConcreteSubject::~ConcreteSubject(){}

void ConcreteSubject::Request()
{
    cout << "ConcreteSubject::Request" << endl;
}


Proxy::Proxy(Subject* sub)
{
    this->_sub = sub;
}

Proxy::~Proxy()
{
    delete this->_sub;
}

void Proxy::Request()

{
    cout << "Proxy Request..." << endl;
    _sub->Request();
}

