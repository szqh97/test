#include "Product.h"
#include "AbstractFactory.h"


int main ( int argc, char *argv[] )
{
    AbstracFactory* cf1 = new ConcreteFactory1();
    cf1->createProductA()->Operation();
    cf1->createProductB()->Operation();
    AbstracFactory* cf2 = new ConcreteFactory2();
    cf2->createProductA()->Operation();
    cf2->createProductB()->Operation();
    delete cf1;
    cf1 = 0;
    delete cf2;
    cf2 = 0;
    return 0;
}			/* ----------  end of function main  ---------- */

