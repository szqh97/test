//Facade.cpp 
#include "Facade.h"
#include <iostream>
using namespace std;
Subsystem1::Subsystem1(){}

Subsystem1::~Subsystem1(){}

void Subsystem1::Operation()
{
    cout << "Subsystem1 Operation" << endl;
}

Subsystem2::Subsystem2(){}

Subsystem2::~Subsystem2(){}

void Subsystem2::Operation()
{
    cout << "Subsystem2 Operation" << endl;
}

Facade::Facade()
{
    this->_subs1 = new Subsystem1();
    this->_subs2 = new Subsystem2();
}

Facade::~Facade()
{
    delete _subs1, _subs1 = NULL;
    delete _subs2, _subs2 = NULL;
}
void Facade::OperationWrapper()
{
    this->_subs1->Operation();
    this->_subs2->Operation();
}
