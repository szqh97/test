#include "Observer.h"
#include <iostream>

using namespace std;

int main ( int argc, char *argv[] )
{

    Customer *c = new Customer();
    WelcomeLetter *w = new WelcomeLetter();
    AddrVerification *a = new AddrVerification();
    c->attach(w);
    c->attach(a);
    c->notify();
    delete c;
    delete w;
    delete a;

    return 0;
}			/* ----------  end of function main  ---------- */
