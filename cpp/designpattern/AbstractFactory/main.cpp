#include "Product.h"
#include "AbstractFactory.h"


int main ( int argc, char *argv[] )
{
    AbstracFactory* cf1 = new ConcreteFactory1();

    AbstractProductA* cpa = cf1->createProductA();
    cpa->Operation();
    AbstractProductB* cpb = cf1->createProductB();
    cpb->Operation();
    delete cpa;
    delete cpb;
    AbstracFactory* cf2 = new ConcreteFactory2();
    cpa = cf2->createProductA();
    cpa->Operation();
    cpb = cf2->createProductB();
    cpb->Operation();
    delete cpa;
    delete cpb;
    cpa = 0;
    cpb = 0;
    delete cf1;
    cf1 = 0;
    delete cf2;
    cf2 = 0;
    return 0;

}			/* ----------  end of function main  ---------- */

