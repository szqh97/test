#include "Circle.h"
#include "XX_Circle.h"

Circle::Circle(XX_Circle* xxcircle)
{
    this->myXX_Circle = xxcircle;
}

Circle::~Circle()
{
}

void Circle::display()
{
    this->myXX_Circle->displayIt();
}
