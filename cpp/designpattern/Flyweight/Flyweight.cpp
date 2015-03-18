#include "Flyweight.h"
#include <iostream>
Flyweight::Flyweight(const string& intrinsicState)
{
    this->_instrisicState = intrinsicState;
}

Flyweight::~Flyweight(){}

void Flyweight::Operation(const string& extrinsicState){}

string Flyweight::GetIntrinsicState()
{
    return this->_instrisicState;
}

ConcreteFlyweight::ConcreteFlyweight(const string& intrinsicState):Flyweight(intrinsicState)
{
    cout << "ConcreteFlyweight Building..." << intrinsicState << endl;
}

ConcreteFlyweight::~ConcreteFlyweight(){}

void ConcreteFlyweight::Operation(const string& extrinsicState)
{
    cout << "ConcreteFlyweight: out" << this->GetIntrinsicState() << "\n Out extrinsicState" << endl;
}
