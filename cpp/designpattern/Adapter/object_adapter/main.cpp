#include "adapter.h"
#include <iostream>
using namespace std;


int main ( int argc, char *argv[] )
{
    Adaptee* ade = new Adaptee();
    Target* adt = new Adapter(ade);
    adt->Request();
    delete ade;
    delete adt;
    return 0;
}			/* ----------  end of function main  ---------- */

