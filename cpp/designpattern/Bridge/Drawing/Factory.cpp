#include "Factory.h"

Factory::Factory(){}

Factory::~Factory(){}

Shape** Factory::getShape()
{
    Shape **myShapes;

    V1Drawing* v1d = new V1Drawing();
    Rectangle* rect = new Rectangle(v1d, 1, 1, 2, 2);
    *myShapes = rect;

    return myShapes;
}

