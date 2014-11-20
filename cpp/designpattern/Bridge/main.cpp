#include "Abstraction.h"
#include "AbstractionImpl.h"
#include <iostream>

using namespace std;

int main ( int argc, char *argv[] )
{
    AbstractionImpl *impl = new ConcreteAbstractionImplA();
    Abstraction *abs = new RefinedAbstraction(impl);
    abs->Operation();
    delete impl;
    delete abs;
    return 0;
}			/* ----------  end of function main  ---------- */

