#include "Product.h"
#include <iostream>

using namespace std;
AbstractProductA::AbstractProductA(){}

AbstractProductA::~AbstractProductA(){}

AbstractProductB::AbstractProductB(){}

AbstractProductB::~AbstractProductB(){}

ProductA1::ProductA1(){}

ProductA1::~ProductA1(){}

void ProductA1::Operation()
{
    cout << "ProductA1::Operation()" << endl;
}

ProductA2::ProductA2(){}

ProductA2::~ProductA2(){}

void ProductA2::Operation()
{
    cout << "ProductA2::Operation()" << endl;
}

ProductB1::ProductB1(){}

ProductB1::~ProductB1(){}

void ProductB1::Operation()
{
    cout << "ProductB1::Operation()" << endl;
}

ProductB2::ProductB2(){}

ProductB2::~ProductB2(){}

void ProductB2::Operation()
{
    cout << "ProductB2::Operation()" << endl;
}



