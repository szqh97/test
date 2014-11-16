#include "Client.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Factory.h"
#include <iostream>

using namespace std;
Client::Client(){}
Client::~Client(){}


int main ( int argc, char *argv[] )
{
    Shape** myShapes ;
    Factory myFactory;
    myShapes = myFactory.getShape();
    for (int i = 0; i < sizeof(myShapes)/ sizeof(myShapes[0]); ++i)
    {
        cout << i << endl;
        //myShapes[i]->draw();
    }
    return 0;
}			/* ----------  end of function main  ---------- */

