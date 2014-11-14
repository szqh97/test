#include "adapter.h"
#include <iostream>
using namespace std;
Target::Target(){}

Target::~Target(){}

void Target::Request()
{
    std::cout << "Target::Request" << std::endl;
}

Adaptee::Adaptee() {}

Adaptee::~Adaptee(){}

void Adaptee::SpecificRequest()
{
    std::cout << "Adaptee::SpecificRequest" << std::endl;
}

Adapter::Adapter(Adaptee* ade)
{
    this->_ade = ade;
}

Adapter::~Adapter(){}

void Adapter::Request()
{
    this->_ade->SpecificRequest();
}


