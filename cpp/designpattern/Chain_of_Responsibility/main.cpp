#include "Handle.h"
#include <iostream>

using namespace std;

int main ( int argc, char *argv[] )
{
    Handle *h1 = new ConcreteHandleA();
    Handle *h2 = new ConcreteHandleB();
    h1->setSuccessor(h2);
    h1->HandleRequest();
    h2->HandleRequest();
    delete h1;

    return 0;
}			/* ----------  end of function main  ---------- */

