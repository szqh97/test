#include "builder.h"
#include <iostream>
#include <string>
using namespace std;
Builder::Builder(){}
Builder_KindOne::Builder_KindOne()
{
    cout << "kind one is creating ..." << endl;
    product = new ProdcutOne();
}

Product* Builder::getProduct()
{
    if (product)
        return product;
}
#if 0
Product* Builder_KindOne::getProduct()
{
    if (product)
        return product;
}
#endif

void Builder_KindOne::buildPartHead(const string str)
{
    product->setHeadColor(str);
}

void Builder_KindOne::buildPartBody(const string str)
{
    product->setBodyColor(str);
}
void Builder_KindOne::buildPartFoot(const string str)
{
    product->setFootColor(str);
}

Builder_KindTwo::Builder_KindTwo()
{
    cout << "kind Two is creating ..." << endl;
    product = new ProdcutTwo();
}
#if 0
Product* Builder_KindTwo::getProduct()
{
    if (product)
        return product;
}
#endif
void Builder_KindTwo::buildPartHead(const string str)
{
    product->setHeadColor(str);
}

void Builder_KindTwo::buildPartBody(const string str)
{
    product->setBodyColor(str);
}
void Builder_KindTwo::buildPartFoot(const string str)
{
    product->setFootColor(str);
}

Builder_KindThree::Builder_KindThree()
{
    cout << "kind Three is creating ..." << endl;
    product = new ProdcutThree();
}
#if 0
Product* Builder_KindThree::getProduct()
{
    if (product)
        return product;
}
#endif
void Builder_KindThree::buildPartHead(const string str)
{
    product->setHeadColor(str);
}

void Builder_KindThree::buildPartBody(const string str)
{
    product->setBodyColor(str);
}
void Builder_KindThree::buildPartFoot(const string str)
{
    product->setFootColor(str);
}

