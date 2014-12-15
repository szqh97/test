#include "Template.h"
#include <iostream>

using namespace std;

AbstractClass::AbstractClass(){}

AbstractClass::~AbstractClass(){}

void AbstractClass::TemplateMethod()
{
    cout << "AbstractClass::TemplateMethod" <<endl;
    Primitive1();
    Primitive2();
}

ConcreteClass1::ConcreteClass1(){}

ConcreteClass1::~ConcreteClass1(){}

void ConcreteClass1::Primitive1()
{
    cout << "ConcreteClass1::Primitive1" << endl;
}

void ConcreteClass1::Primitive2()
{
    cout << "ConcreteClass1::Primitive2" << endl;
}

ConcreteClass2::ConcreteClass2(){}

ConcreteClass2::~ConcreteClass2(){}

void ConcreteClass2::Primitive1()
{
    cout << "ConcreteClass2::Primitive1" << endl;
}

void ConcreteClass2::Primitive2()
{
    cout << "ConcreteClass2::Primitive2" << endl;
}

