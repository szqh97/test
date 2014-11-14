#include <iostream>
#include "XX_Circle.h"
#include "Circle.h"

using namespace std;

int main ( int argc, char *argv[] )
{

     XX_Circle xxcircle = XX_Circle();
     //xxcircle.displayIt();
     cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
     Circle c = Circle(&xxcircle);
     c.display();


    return 0;
}			/* ----------  end of function main  ---------- */

