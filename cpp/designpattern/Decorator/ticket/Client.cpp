#include <iostream>
#include "Factory.h"
#include "Component.h"

using namespace std;


int main ( int argc, char *argv[] )
{
    Factory myfactory;
    Component *com = myfactory.getComponent();
    //com->prtTicket();
    //delete com;

    return 0;
}			/* ----------  end of function main  ---------- */
