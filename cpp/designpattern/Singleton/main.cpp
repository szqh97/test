#include "Singleton.h"
#include <iostream>

using namespace std;


int main ( int argc, char *argv[] )
{
    Singleton* sgn = Singleton::getInstance();
    sgn = Singleton::getInstance();

    delete sgn;


    return 0;
}			/* ----------  end of function main  ---------- */

